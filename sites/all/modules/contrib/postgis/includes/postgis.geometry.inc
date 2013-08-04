<?php

/**
 * @file
 * PostGIS geometry classes.
 */

class PostgisGeometryException extends Exception {
}


/**
 * warpper arround wkt strings
 * converts EWKT to WKT
 */
class postgis_Wkt {
  private $wkt, $srid;

  function __construct($wkt) {
    // check if the wkt is an EWKT string. if it is, use the srid
    // convert the ewkt to wkt
    if (preg_match('/^SRID\=([0-9]+);(.*)/i', $wkt, $matches)) {
      $this->srid = $matches[1];
      $this->wkt = $matches[2];
    }
    else {
      $this->wkt = $wkt;
    }
  }

  /**
   * return a WKT string
   */
  function getWktString() {
    return $this->wkt;
  }

  function getSrid() {
    return $this->srid;
  }

  function hasSrid() {
    return !empty($this->srid);
  }

  /**
   * return the wktstring wrapped in a geometry collection
   */
  function getCollectionWktString() {
    if (stripos($this->wkt, 'GEOMETRYCOLLECTION') !== 0) {
      return 'GEOMETRYCOLLECTION(' . $this->wkt . ')';
    }
    return $this->wkt;
  }
}

/**
 * Provides a set of postgis_geometry with same geometry type and projection.
 */
class PostgisGeometrySet {

  private $geometries = array();
  private $cardinality, $type, $srid, $multi;

  /**
   * Creates an empty geometry set.
   *
   * @param string $type
   *   Geometry type.
   * @param int $srid
   *   Spatial projection.
   * @param int $cardinality
   *   Number of geometries. -1 means unlimited number of geometry.
   */
  function __construct($type, $srid, $cardinality = -1) {
    $this->type = $type;
    $this->srid = $srid;
    $this->multi = $this->isMulti($type);
    $this->cardinality = $cardinality;
  }

  /**
   * Checks if geometry type is a collection of geometries.
   * @param string $type Geometry type
   * @return boolean TRUE if type is a collection.
   */
  protected function isMulti($type) {
    switch ($type) {
      case POSTGIS_PRIMITIVE_MULTIPOINT:
      case POSTGIS_PRIMITIVE_MULTILINESTRING:
      case POSTGIS_PRIMITIVE_MULTIPOLYGON:
        return TRUE;
      case POSTGIS_PRIMITIVE_GEOMETRYCOLLECTION:
      case POSTGIS_PRIMITIVE_POINT:
      case POSTGIS_PRIMITIVE_LINESTRING:
      case POSTGIS_PRIMITIVE_POLYGON:
        return FALSE;
    }
    throw new PostgisGeometryException(t('Geometry type not supported.'));
  }

  /**
   * Validates each geometry.
   *
   * @return array
   *   Reason array as described in API documentation for hook_field_validate
   *   if not valid, otherwise null.
   */
  function validate() {
    if (($this->cardinality != -1) && ($this->count() > $this->cardinality)) {
      return array(
        'error' => 'postgis_cardinalitymismatch',
        'message' => t('Too many geometries. Got @result, was expecting @cardinality.',
          array(
            '@result' => $this->count(),
            '@cardinality' => $this->cardinality,
          )),
      );
    }

    foreach ($this->geometries as $geometry) {
      $result = $geometry->validate();
      if ($result !== NULL) {
        return $result;
      }
    }
  }

  /**
   * Returns length of all geometries. See PostgisGeometry->length
   * for a more precise definition of length.
   *
   * @param string $unit
   *   Abbreviation of the units, e.g. "km".
   *
   * @return int
   *   Length in given units.
   */
  function length($unit) {
    $length = 0;
    foreach ($this->geometries as $geometry) {
      $length += $geometry->length($unit);
    }
    return $length;
  }

  /**
   * Count geometries.
   */
  function count() {
    return count($this->geometries);
  }

  /**
   * Add a geometry to geometries.
   */
  function add(PostgisGeometry $geometry) {
    if ($geometry->getSrid() !== $this->srid) {
      $geometry->transform($this->srid);
    }
    $this->geometries[] = $geometry;
  }

  /**
   * Get geometry at a given index.
   */
  function get($index) {
    return $this->geometries[$index];
  }

  /**
   * Create a new set containing the diffrence of each geometry.
   */
  function diff($set) {

    if (get_class($set) !== 'postgis_geometry_set') {
      throw new PostgisGeometryException('not a postgis_geometry_set');
    }

    $diff_set = new PostgisGeometrySet($this->type, $this->srid, $this->cardinality);

    foreach ($this->geometries as $index => $geometry) {
      if ($index < $set->count()) {
        $geometry = $geometry->diff($set->get($index));
      }
      $diff_set->add($geometry);
    }

    return $diff_set;
  }


  /**
   * Add geometries from text. The existing geometries are kept
   * and the new geometries are added behind.
   * @param $wktString string
   */
  function fromText($wktString) {

    // Catch empty WKT and GEOMETRYCOLLECTION coming from OpenLayers.
    if (empty($wktString) || $wktString === 'GEOMETRYCOLLECTION()' || $wktString === 'GEOMETRYCOLLECTION(EMPTY)') {
      return;
    }

    $wkt = new postgis_Wkt($wktString);
    // Return WKT from (maybe) EWKT and add GEOMETRYCOLLECTION if missing for OpenLayers compability.
    $wktString = $wkt->getCollectionWktString();
    $wktSrid = $this->srid;
    if ($wkt->hasSrid()) {
      $wktSrid = $wkt->getSrid();
    }

    try {
      if ($this->multi) {

        // Convert geometrycollection with single geometries to multi geometry.
        // For example if OpenLayers sends a point in a GeometryCollection,
        // the following query would transfer it to a point in a MultiPoint.
        // This is done of type-compability with the selection geometry type.
        $wktMulti = db_query("SELECT ST_AsText(ST_Multi(ST_Collect(a.geom))) AS wkt
          FROM (SELECT (ST_Dump(ST_GeomFromText(:wkt))).geom as geom) AS a",
          array(':wkt' => $wktString))->fetchField();

        $geometry = new PostgisGeometry($this->type, $wktSrid);
        $geometry->fromText($wktMulti);
        $this->add($geometry);

      }
      else {

        // Convert geometrycollection  to single geometries.
        $rows = db_query("SELECT ST_AsText(a.geom) as wkt FROM (
          SELECT (ST_Dump(ST_GeomFromText(:wkt))).geom as geom) AS a;",
          array(':wkt' => $wktString));

        foreach ($rows as $row) {
          $geometry = new PostgisGeometry($this->type, $wktSrid);
          $geometry->fromText($row->wkt);
          $this->add($geometry);
        }
      }
    }
    catch (PDOException $e) {

      // Just add broken WKT, will be validated later.
      $geometry = new PostgisGeometry($this->type, $wktSrid);
      $geometry->fromText($wktString);
      $this->add($geometry);
    }
  }

  /**
   * Add geometries from binary.
   *
   * @param array $items
   *   Geometries stored with key "geometry".
   */
  function fromGeometry($items) {

    foreach ($items as $item) {
      if (isset($item['geometry'])) {
        $geometry = new PostgisGeometry($this->type, $this->srid);
        $geometry->fromGeometry($item['geometry']);
        $this->add($geometry);
      }
    }
  }

  /**
   * Returns text representation of all geometries.
   * @return string
   */
  function getText() {

    $wkt = array();
    foreach ($this->geometries as $geometry) {
      $single_wkt = $geometry->getText();
      if (mb_stripos($single_wkt, 'GEOMETRYCOLLECTION(') === 0) {
        // Remove nested collections.
        $single_wkt = mb_substr($single_wkt, mb_strlen('GEOMETRYCOLLECTION('),
            mb_strlen($single_wkt) - 1 - mb_strlen('GEOMETRYCOLLECTION('));
      }
      $wkt[] = $single_wkt;
    }
    if (count($wkt) === 0) {
      // An empty collection needs to contain the string EMPTY to be valid.
      $wkt[] = 'EMPTY';
    }
    return 'GEOMETRYCOLLECTION(' . implode(',', $wkt) . ')';
  }

  /**
   * Calculate bounding box of all geometries.
   */
  function getBox($buffer = 0, $srid = NULL) {

    $items = array();
    foreach ($this->geometries as $index => $geometry) {
      $items[':geo' . $index] = $geometry->getText();
    }
    $keys = implode('::geometry , ', array_keys($items));

    $items[':buffer'] = $buffer;
    $items[':target_srid'] = empty($srid) ? $this->srid : $srid;
    $items[':source_srid'] = $this->srid;

    $box = db_query('SELECT Box2D(ST_Transform(ST_SetSRID(ST_Buffer(
      ST_Union(' . $keys . '::geometry), :buffer), :source_srid), :target_srid))',
      $items)->fetchField();

    return $box;
  }

  /**
   * Returns an array of geometries.
   *
   * Text representation is stored with key "wkt" and
   * binary representation is stored with key "geometry".
   *
   * @return array
   *   Array of text and binary representation of all geometries.
   */
  function getItems() {

    $items = array();
    foreach ($this->geometries as $geometry) {
      $items[] = array(
        'wkt' => $geometry->getText(),
        'geometry' => $geometry->getGeometry(),
      );
    }
    return $items;
  }

  /**
   * Checks if geometries are empty.
   */
  function isEmpty() {
    return empty($this->geometries);
  }

  /**
   * Geometries get transformed to spatial reference system 
   * referenced by the SRID integer parameter.
   *
   * @param integer $srid
   *   SRID of target spatial reference system.
   */
  function transform($srid) {
    foreach ($this->geometries as $geometry) {
      $geometry->transform($srid);
    }
    $this->srid = $srid;
  }
}

/**
 * Simple class for a PostGIS geometry.
 */
class PostgisGeometry {

  private $geometry, $wkt, $type, $srid;

  /**
   * Creates an empty geometry.
   *
   * @param String $type
   *   Geometry type.
   * @param int $srid
   *   Spatial projection.
   */
  function __construct($type, $srid) {
    $this->type = $type;
    $this->srid = $srid;
  }

  /**
   * Add geometry from text.
   */
  function fromText($wkt) {
    $this->geometry = NULL;

    // check if the wkt is an EWKT string. if it is, use the srid
    // convert the ewkt to wkt
    $wktObj = new postgis_Wkt($wkt);
    $this->wkt = $wktObj->getWktString();
    if ($wktObj->hasSrid()) {
      $this->srid = $wktObj->getSrid();
    }
  }

  /**
   * Adds geometries from binary.
   */
  function fromGeometry($geometry) {
    $this->geometry = $geometry;
    $this->wkt = NULL;
  }

  /**
   * Returns text representation of geometry.
   */
  function getText() {
    if (is_null($this->wkt)) {
      $this->wkt = db_query("SELECT ST_AsText(:geometry)",
          array(':geometry' => $this->geometry))->fetchField();
    }
    return $this->wkt;
  }

  /**
   * return the SRID of the geometry
   */
  function getSrid() {
    return $this->srid;
  }

  /**
   * Returns KML representation of geometry.
   */
  function getKML() {

    $geometry = is_null($this->wkt) ? $this->geometry : $this->wkt;

    return db_query("SELECT ST_AsKML(:geometry)", array(':geometry' => $geometry))->fetchField();
  }

  /**
   * Returns binary representation of geometry.
   */
  function getGeometry() {
    if (is_null($this->geometry)) {
      $this->geometry = db_query("SELECT ST_GeomFromText(:wkt, :srid)",
        array(':wkt' => $this->wkt, ':srid' => $this->srid))->fetchField();
    }
    return $this->geometry;
  }

  /**
   * Calculates diffrence to a given geometry.
   *
   * @param PostgisGeometry $geometry
   *   Geometry which this instance will be compared to.
   *
   * @return PostgisGeometry
   *   Geometry of diffrence.
   */
  function diff($geometry) {

    if (get_class($geometry) !== 'postgis_geometry') {
      throw new PostgisGeometryException('not postgis_geometry');
    }

    $geo_a = $this->getGeometry();
    $geo_b = $geometry->getGeometry();

    $geo_diff = db_query("SELECT ST_Union(ST_Difference(:geo_a, :geo_b), ST_Difference(:geo_b, :geo_a))",
        array(':geo_a' => $geo_a, ':geo_b' => $geo_b))->fetchField();
    $geo_type = db_query("SELECT GeometryType(:geo_diff)",
        array(':geo_diff' => $geo_diff))->fetchField();

    $diff = new PostgisGeometry($geo_type, $this->srid);
    $diff->fromGeometry($geo_diff);

    return $diff;
  }

  /**
   * Validates geometry.
   *
   * @return array
   *   Reason array as described in API documentation for hook_field_validate
   *   if not valid, otherwise null.
   */
  function validate() {

    $geo = is_null($this->wkt) ? $this->geometry : $this->wkt;

    try {
      $result = db_query("SELECT ST_GeometryType(:geo), ST_IsValid(:geo), ST_IsValidReason(:geo) as reason",
          array(':geo' => $geo))->fetchAssoc();

      // Return reason if geometry is not valid.
      if (!$result['st_isvalid']) {
        return array(
          'error' => 'postgis_unparsable',
          'message' => t('Not a valid geometry: @reason.', array('@reason' => $result['reason'])),
        );
      }

      $result_type = drupal_strtoupper(drupal_substr($result['st_geometrytype'], 3));

      // Return error if geometry type is unexpected.
      if (($this->type !== POSTGIS_PRIMITIVE_GEOMETRYCOLLECTION) && ($result_type != $this->type)) {
        return array(
          'error' => 'postgis_typemismatch',
          'message' => t('Wrong geometry type. Got @result, was expecting @type.',
            array('@result' => $result_type, '@type' => $this->type)),
          );
      }
    }
    catch (PDOException $e) {
      // TODO: catch only WKT parse errors.
      return array(
        'error' => 'postgis_unparsable',
        'message' => t('Unable to parse WKT: ' . $geo),
      );
    }
  }

  /**
   * Returns length of geometry using ST_Length().
   * The perimeter length is returned for areas.
   *
   * @param string $unit
   *   Abbreviation of the units, either "km" or "m"
   *
   * @return int
   *   Length in given units.
   */
  function length($unit) {

    $geo = is_null($this->wkt) ? $this->geometry : $this->wkt;

    // An implicit conversion to geography is applied
    // which results in the length in meters.
    $result = db_query("SELECT ST_Length(:geo, true)", array(':geo' => $geo))->fetchField();

    switch ($unit) {
      case 'm':
        return round($result);
      case 'km':
        return round($result / 1000);
      default:
        throw new PostgisGeometryException('Only m and km are supported for length retrieval.');
    }
  }

  /**
   * Checks if geometry is empty.
   *
   * @return boolean TRUE if the geometry is not yet set.
   */
  function isEmpty() {
    $geo = is_null($this->wkt) ? $this->geometry : $this->wkt;
    return empty($geo);
  }

  /**
   * Geometry gets transformed to spatial reference system 
   * referenced by the SRID integer parameter.
   *
   * @param integer $srid
   *   SRID of target spatial reference system.
   */
  function transform($srid) {
    $geometry = $this->getGeometry();
    $this->geometry = db_query("SELECT ST_Transform(:geometry::geometry, :srid::integer)", 
      array(':geometry' => $geometry, ':srid' => $srid))->fetchField();
    $this->srid = $srid;
    $this->wkt = NULL;
  }
}


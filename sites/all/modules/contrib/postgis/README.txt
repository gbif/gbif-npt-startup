
Handling of multi/single geometries and field cardinality
=========================================================

The field cardinality (Number of values) will only limit the number of
geometries one can add to a field, regardless how they are stored internally.
The multi/single geometry types will affect how data is stored in the database.
If you select a single geometry type, each geometry will be saved to a new row.
For multi geometry types all geometries will be saved to a single row.
Input should always be a single WKT string.


OpenLayers integration
======================

* optional
* behaviors
* GEOMETRYCOLLECTION


<?php
/**
 * @file
 * Description of a HTTP request's response
 */
class geoserver_httpresponse {
    /**
     * @var string
     */
    public $url;
    /**
     * @var string Response body
     */
    public $data;
    /**
     * @var integer HTTP status code of response
     */
    public $code;
}
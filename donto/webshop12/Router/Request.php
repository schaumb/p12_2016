<?php

class Request
{
    protected $queryString;
    protected $requestUri;

    function __construct()
    {
        $this->queryString = $_SERVER["QUERY_STRING"];
        $this->requestUri = $_SERVER["REQUEST_URI"];
    }
    
    public function getRoute()
    {
        $route = substr($this->requestUri, strpos($this->requestUri, ".php") + 4);

        if(strlen($route) === 0)
            $route = "/";

        return $route;
    }
}
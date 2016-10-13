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
        //$route = substr($this->requestUri, strpos(substr($this->requestUri, 0, -(strlen($this->queryString) + 1)), ".php") + 4);
        $route = $this->requestUri;

        if(strlen($route) === 0)
            $route = "/";

        return $route;
    }
}
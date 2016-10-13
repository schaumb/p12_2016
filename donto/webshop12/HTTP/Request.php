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
        $questionmark = strpos($this->requestUri, "?");
        $php = strpos($this->requestUri, ".php");

        if($php !== false && $php < $questionmark)
            $route = substr($this->requestUri, $php + 4);
        else
            $route = $this->requestUri;

        if(strlen($route) === 0)
            $route = "/";

        return $route;
    }
}
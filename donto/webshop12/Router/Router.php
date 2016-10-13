<?php

include_once("Request.php");

class Router
{
    protected $routes = array();

    protected $request;

    function __construct()
    {
        $this->request = new Request();
    }

    public function addRoute($route, $controllerFunction)
    {
        $this->routes[] = array(
            "route" => $route,
            "controllerFunction" => $controllerFunction,
        );

        return $this;
    }
    
    public function execAction()
    {
        $currentRoute = $this->request->getRoute();
        foreach ($this->routes as $route)
        {
            if($route["route"] == $currentRoute )
            {
                $route["controllerFunction"]($this->request);
                return;
            }
        }
        
        return;
    }
}
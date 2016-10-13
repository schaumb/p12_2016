<?php

include_once("config.php");
include_once("Router/Router.php");

$ROUTER = new Router();

$controllerPHPs = scandir("Controller");
foreach ($controllerPHPs as $controllerPHP)
{
    if(substr($controllerPHP, -4) == ".php")
        include_once("Controller/" . $controllerPHP);
}

$ROUTER->execAction();
<?php

include_once("config.php");
include_once("Db/Database.php");
include_once("HTTP/Router.php");

$DATABASE = new Database();
$ROUTER = new Router();

if(!$DATABASE->getConnection())
    include_once("install.php");


$controllerPHPs = scandir("Controller");
foreach ($controllerPHPs as $controllerPHP) {
    if (substr($controllerPHP, -4) == ".php")
        include_once("Controller/" . $controllerPHP);
}

$ROUTER->execAction($DATABASE);

<?php

$ROUTER->addRoute("/", "indexAction");

function indexAction($request, Database &$db)
{
    $products = $db->findAll("Product");

    include_once("../Resources/layout.html.php");
}
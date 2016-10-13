<?php

$ROUTER->addRoute("/", "indexAction");

function indexAction($request, Database &$db)
{
    $products = $db->findAll("Product");
    

    include_once(getcwd() . "/Resources/views/product/list.html.php");
}
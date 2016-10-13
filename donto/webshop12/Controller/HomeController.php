<?php

$ROUTER->addRoute("/", "indexAction");

function indexAction($request, Database &$db)
{
    $products = $db->findAll("Product");

    var_dump($products->fetchAll());
}
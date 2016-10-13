<?php

$ROUTER->addRoute("/", "indexAction");

include_once (dirname(__FILE__) . "/../Entity/Product.php");

function indexAction($request, Database &$db)
{
    $products = $db->findAll("Product")->fetchAll();

    foreach ($products as &$product)
    {
        $product = Product::createFromArray($product);
    }

    include_once(getcwd() . "/Resources/views/product/list.html.php");
}
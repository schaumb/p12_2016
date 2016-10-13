<?php

$content = "";

foreach ($products as $product)
{
    $content .= "<div class='productCard'>
    <div class='productCardName'>" . $product->getProductName() . "</div>
    <div class='productCardImage'></div>
    <div class='productCardPrice'>" . $product->getPrice() . "</div>
    <div class='productCardDescription'>" . $product->getDescription() . "</div>
</div>\n";
}


include_once(dirname(__FILE__) . "/../layout.html.php");
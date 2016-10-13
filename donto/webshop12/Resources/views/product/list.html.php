<?php

$content = "";

foreach ($products as $product)
{
    $content .= "<div class=\"productCard\">" . $product["ProductName"] . "</div>\n";
}


include_once(dirname(__FILE__) . "/../layout.html.php");
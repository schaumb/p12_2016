<?php

if(!isset($content)) $content = "";

$title = "Webshop12";
$body = "<div id=\"menu-container\">
        <div id=\"menu\">
            <h2>Menü</h2>
            <ul>
                <li>Haha</li>
                <li>Hehe</li>
            </ul>
        </div>
    </div>
    <div id=\"content-container\">" . $content . "</div>";

include_once("base.html.php");
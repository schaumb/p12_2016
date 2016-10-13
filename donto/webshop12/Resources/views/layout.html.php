<?php

if(!isset($content)) $content = "";

$script = '
    var pageSize = -1;
    var products = [];

    $(document).ready(function () {
        $("#pagination-select select").change(function (event) {
            pageSize = $("#pagination-select select").val();
            
            $("#pagination-buttons").html("");
            
            for(var i = 0; i < Math.ceil(products.length/pageSize); i++)
            {
                $("#pagination-buttons").append(
                    $("<button>").text(i)
                    .click();
                );
            }
        });
        
        $("#content-container").children().each(function (index, element) {
            products.push(element);
        });
    });
';

$title = "Webshop12";
$body = "<div id='menu-container'>
        <div id='menu'>
            <h2>Menü</h2>
            <ul>
                <li>Haha</li>
                <li>Hehe</li>
            </ul>
        </div>
    </div>
    <div id='content-container'>" . $content . "
</div>
<div id='pagination-container'>
    <div id='pagination-select'>
         <select autocomplete='off'>
              <option value='all'>Összes</option>
              <option value='10'>10</option>
              <option value='25'>25</option>
              <option value='50'>50</option>
              <option value='100'>100</option>
          </select> 
    </div>
    <div id='pagination-buttons'></div>
    </div>";

include_once("base.html.php");
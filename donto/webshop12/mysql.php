<?php

include_once("config.php");

try {
    $MYSQL = new PDO("mysql:=" . MYSQL_DATABASE_NAME . ";host=" . MYSQL_HOST, MYSQL_USER, MYSQL_PASSWORD);
} catch (PDOException $e) {
    echo 'Connection failed: ' . $e->getMessage();
}
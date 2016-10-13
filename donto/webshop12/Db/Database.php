<?php

class Database
{
    protected $connection;
    
    function __construct()
    {
        try
        {
            $this->connection = $MYSQL = new PDO("mysql:=" . MYSQL_DATABASE_NAME . ";host=" . MYSQL_HOST . ";charset=utf8;", MYSQL_USER, MYSQL_PASSWORD);
        }
        catch (PDOException $e)
        {
            echo 'Connection failed: ' . $e->getMessage();
        }
    }

    public function findAll($entityName)
    {
        $query = $this->connection->query("SELECT * FROM " . MYSQL_DATABASE_NAME . "." . $entityName);
        return $query;
    }
}
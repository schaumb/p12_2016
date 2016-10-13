<?php

class Database
{
    protected $connection = false;
    
    function __construct()
    {
        try
        {
            $this->connection = $MYSQL = new PDO("mysql:dbname=" . MYSQL_DATABASE_NAME . ";host=" . MYSQL_HOST . ";charset=utf8;", MYSQL_USER, MYSQL_PASSWORD);
        }
        catch (PDOException $e)
        {
            echo 'Connection failed: ' . $e->getMessage();

            $this->connection = false;
        }
    }
    
    public function getConnection()
    {
        return $this->connection;
    }

    public function exec($sql)
    {
        $this->connection->exec($sql);
    }

    public function findAll($entityName)
    {
        $query = $this->connection->query("SELECT * FROM " . MYSQL_DATABASE_NAME . "." . $entityName);

        return $query;
    }
}
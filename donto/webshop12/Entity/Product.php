<?php

include_once("Entity.php");

class Product implements Entity
{
    private $ProductId;

    protected $ProductName;

    protected $Description;

    protected $Price;

    protected $Image;

    protected $category;


    public static function createFromArray($arr)
    {
        $product = new Product();

        if(is_array($arr))
        {
            if(isset($arr["ProductId"])) $product->setProductId($arr["ProductId"]);
            if(isset($arr["ProductName"])) $product->setProductName($arr["ProductName"]);
            if(isset($arr["Description"])) $product->setDescription($arr["Description"]);
            if(isset($arr["Price"])) $product->setPrice($arr["Price"]);
            if(isset($arr["Image"])) $product->setImage($arr["Image"]);
            if(isset($arr["category"])) $product->setCategory($arr["category"]);
        }

        return $product;
    }

    public function getDatabaseTableDefinition()
    {
        return "CREATE TABLE webshop12.Product
                (
                    ProductId INT PRIMARY KEY NOT NULL AUTO_INCREMENT,
                    ProductName VARCHAR(255) COLLATE utf8_unicode_ci,
                    Description TEXT COLLATE utf8_unicode_ci,
                    Price INT,
                    Image VARCHAR(255) COLLATE utf8_unicode_ci
                );";
    }

    public function setProductId($productId)
    {
        $this->ProductId = $productId;

        return $this;
    }

    public function getProductId()
    {
        return $this->ProductId;
    }

    public function setProductName($productName)
    {
        $this->ProductName = $productName;

        return $this;
    }

    public function getProductName()
    {
        return $this->ProductName;
    }

    public function setDescription($description)
    {
        $this->Description = $description;

        return $this;
    }

    public function getDescription()
    {
        return $this->Description;
    }

    public function setPrice($price)
    {
        $this->Price = $price;

        return $this;
    }

    public function getPrice()
    {
        return $this->Price;
    }

    public function setImage($image)
    {
        $this->Image = $image;

        return $this;
    }

    public function getImage()
    {
        return $this->Image;
    }

    public function setCategory($category)
    {
        $this->category = $category;

        return $this;
    }

    public function getCategory()
    {
        return $this->category;
    }

}
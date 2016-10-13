<?php

class Product
{
    private $ProductId;

    protected $ProductName;

    protected $Description;

    protected $Price;

    protected $Image;



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
        }

        return $product;
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

}
<?php

    require __DIR__ . '/../vendor/autoload.php';

    $dotenv = Dotenv\Dotenv::createImmutable(__DIR__ . "/..");
    $dotenv->load();
    $dotenv->required(["DB_HOST", "DB_USER", "DB_PASSWORD", "DB_NAME", "DB_PORT"]);
    $connection = mysqli_connect(
      $_ENV["DB_HOST"], 
      $_ENV["DB_USER"], 
      $_ENV["DB_PASSWORD"], 
      $_ENV["DB_NAME"], 
      $_ENV["DB_PORT"]
    );
?>

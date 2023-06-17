<?php
header("Access-Control-Allow-Origin: *");
header("Content-Type: text/plain; charset=UTF-8");
header("Access-Control-Allow-Methods: GET");
header("Access-Control-Max-Age: 3600");
header("Access-Control-Allow-Headers: Content-Type, Access-Control-Allow-Headers, Authorization, X-Requested-With");

if ($_SERVER['REQUEST_METHOD'] == 'OPTIONS') {
    return;
}

if($_SERVER['HTTP_AUTHORIZATION'] == null) {
    header("HTTP/1.1 401 Unauthorized");
    return;
}

$value = $_SERVER['HTTP_AUTHORIZATION'];


if (substr($value, 0, strlen("Bearer")) != "Bearer") {
    header("HTTP/1.1 401 Unauthorized");
    return;
}
$token = substr($value, strlen("Bearer "));

if($token != null) {
    echo "logged in as " . $token;
    header("HTTP/1.1 200 Ok");
} else {
    echo "not logged in";
    header("HTTP/1.1 401 Unauthorized");
}
?>
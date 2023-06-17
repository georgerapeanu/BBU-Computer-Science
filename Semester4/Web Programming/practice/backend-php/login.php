<?php
header("Access-Control-Allow-Origin: *");
header("Content-Type: application/json; charset=UTF-8");
header("Access-Control-Allow-Methods: POST");
header("Access-Control-Max-Age: 3600");
header("Access-Control-Allow-Headers: Content-Type, Access-Control-Allow-Headers, Authorization, X-Requested-With");

if ($_SERVER['REQUEST_METHOD'] == 'OPTIONS') {
    return;
}

require_once("connect.php");

$json = file_get_contents('php://input');
$data = json_decode($json, true);

$prepare_statement = $connection->prepare("SELECT COUNT(*) FROM User WHERE username=? AND password=? LIMIT 1");
$prepare_statement->bind_param("ss", $data["username"], $data["password"]);
$prepare_statement->execute();
$result = $prepare_statement->get_result();
$count = $result->fetch_row()[0];

$response = [];

if($count == 0) {
    header("HTTP/1.1 401 Unauthorized");
} else {
    header("HTTP/1.1 200 Ok");
    $response["token"] = $data["username"];
}
echo json_encode($response);
$connection->close();
?>
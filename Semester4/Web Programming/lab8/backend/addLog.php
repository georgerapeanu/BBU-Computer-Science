<?php
header("Access-Control-Allow-Origin: *");
header("Content-Type: application/json; charset=UTF-8");
header("Access-Control-Allow-Methods: POST");
header("Access-Control-Max-Age: 3600");
header("Access-Control-Allow-Headers: Content-Type, Access-Control-Allow-Headers, Authorization, X-Requested-With");
require_once("utils/connect.php");

if ($_SERVER['REQUEST_METHOD'] == 'OPTIONS') {
    return;
}

$json = file_get_contents('php://input');
$data = json_decode($json, true);

$severity = $data["severity"];
$date = $data["logDate"];
$user = $data["user"];
$text = $data["data"];

if (strlen($severity) == 0) {
    header("HTTP/1.1 400 Bad Request");
    $connection->close();
    return;
}

if (strlen($user) == 0) {
    header("HTTP/1.1 400 Bad Request");
    $connection->close();
    return;
}

if (strlen($text) == 0) {
    header("HTTP/1.1 400 Bad Request");
    $connection->close();
    return;
}

$d = DateTime::createFromFormat("Y-m-d", $date);
if (!$d || $d->format("Y-m-d") != $date) {
    header("HTTP/1.1 400 Bad Request");
    $connection->close();
    return;
}

$sql_query = "INSERT INTO Logs (`severity`, `logDate`, `user`, `data`) VALUES (?, ?, ?, ?)";

$stmt = mysqli_prepare($connection, $sql_query);
mysqli_stmt_bind_param($stmt, "ssss", $severity, $date, $user, $text);
mysqli_stmt_execute($stmt);
$stmt->close();
$connection->close();
?>
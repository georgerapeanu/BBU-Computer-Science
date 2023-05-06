<?php
header("Access-Control-Allow-Origin: *");
require_once("utils/connect.php");

if (!is_numeric($_GET["id"])) {
    header("HTTP/1.1 400 Bad Request");
    return;
}
$id = (int) $_GET["id"];

$sql_query = "SELECT * FROM Logs WHERE id=?";
$stmt = mysqli_prepare($connection, $sql_query);
mysqli_stmt_bind_param($stmt, "i", $id);
mysqli_stmt_execute($stmt);
$result = mysqli_stmt_get_result($stmt);

$rows = array();
while ($row = $result->fetch_assoc()) {
    $rows[] = $row;
}

$stmt->close();
$connection->close();

if (count($rows) != 1) {
    header("HTTP/1.1 404 Not Found");
    return;
}

echo json_encode($rows[0]);
?>
<?php
header("Access-Control-Allow-Origin: *");
require_once("utils/connect.php");
$id = (int) $_GET["id"];

$sql_query = "DELETE FROM Logs WHERE `id` = ?";

$stmt = mysqli_prepare($connection, $sql_query);
mysqli_stmt_bind_param($stmt, "i", $id);
mysqli_stmt_execute($stmt);
$stmt->close();
$connection->close();
?>
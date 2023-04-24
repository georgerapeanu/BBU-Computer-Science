<?php
require_once("utils/connect.php");

$sql_query = "SELECT * FROM Logs WHERE 1=1";
$params = [];
$paramsTypes = "";

$start_id = 0;
if (is_numeric($_GET["start_id"])) {
    $start_id = (int) $_GET["start_id"];
}

if (strlen($_GET["user"]) != 0) {
    $sql_query = $sql_query . " AND user LIKE ?";
    array_push($params, "%" . $_GET["user"] . "%");
    $paramsTypes .= "s";

}

if (strlen($_GET["severity"]) != 0) {
    $sql_query = $sql_query . " AND severity LIKE ?";
    array_push($params, "%" . $_GET["severity"] . "%");
    $paramsTypes .= "s";
}

$sql_query .= " LIMIT 4 OFFSET ?";
array_push($params, $start_id);
$paramsTypes .= "i";

$stmt = mysqli_prepare($connection, $sql_query);
mysqli_stmt_bind_param($stmt, $paramsTypes, ...$params);
mysqli_stmt_execute($stmt);
$result = mysqli_stmt_get_result($stmt);

$rows = array();
while ($row = $result->fetch_assoc()) {
    $rows[] = $row;
}

$stmt->close();
$connection->close();

echo json_encode($rows);

?>
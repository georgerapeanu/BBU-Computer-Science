<?php
    require_once("utils/connect.php");
    $stmt = null;

    
    if (strlen($_GET["user"]) != 0) {
        $stmt = mysqli_prepare($connection, "SELECT TOP 4 FROM Logs WHERE user == ? AND id >= ?");
        mysqli_stmt_bind_param($stmt, "s", $_GET["user"]);
    } else {
        $stmt = mysqli_prepare($connection, "SELECT TOP 4 FROM Logs WHERE id >= ?");
    }
    $start_id = 0;
    if(is_integer($_GET["start_id"])) {
        $start_id = (int)$_GET["start_id"];
    }
    mysqli_stmt_bind_param($stmt, "i", $start_id);
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
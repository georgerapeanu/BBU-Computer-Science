<?php
    require_once("utils/connect.php");
    $id = $_POST["id"];
    $severity = $_POST["severity"];
    $date = $_POST["date"];
    $user = $_POST["user"];
    $text = $_POST["text"];

    if(strlen($severity) == 0){
        header("HTTP/1.1 400 Bad Request");
        $connection->close();
        return ;
    }

    if(strlen($user) == 0){
        header("HTTP/1.1 400 Bad Request");
        $connection->close();
        return ;
    }

    if(strlen($text) == 0){
        header("HTTP/1.1 400 Bad Request");
        $connection->close();
        return ;
    }

    $d = DateTime::createFromFormat("Y-m-d", $date);
    if(!$d || $d->format("Y-m-d") != $date) {
        header("HTTP/1.1 400 Bad Request");
        $connection->close();
        return ;
    }

    $sql_query = "UPDATE Logs SET `severity` = ?, `logDate` = ?, `user` = ?, `data` = ? WHERE `id` = ?";

    $stmt = mysqli_prepare($connection, $sql_query);
    mysqli_stmt_bind_param($stmt, "ssssi", $severity, $date, $user, $text, $id);
    mysqli_stmt_execute($stmt);
    $stmt->close();
    $connection->close();
?>

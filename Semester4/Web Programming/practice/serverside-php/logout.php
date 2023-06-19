<?php
    setcookie("user", "", time() - 300);
    header("Location: /index.php");
?>
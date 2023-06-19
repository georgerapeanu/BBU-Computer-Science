<?php
    session_start();
    if($_COOKIE["user"] == null) {
        header("Location: /login.php");
        return ;
    }
?>

<form method="GET" action="logout.php">
    <button type="submit"> Logout </button>
</form>

Succesfully logged in as <?php echo $_COOKIE["user"]?>.

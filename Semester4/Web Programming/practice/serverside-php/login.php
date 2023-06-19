<?php
     session_start(); 
?>

<!DOCTYPE html>
<html>
    <head> 
        <title> Basic frontend login </title>
        <link rel="stylesheet" type="text/css" href="login.css">
        <script src="utils/jquery-3.7.0.js"> </script>
        <script src="utils/constants.js"></script>
        <script src="utils/cookie_util.js"></script>
    </head>
    <body> 
        <h2>Login</h2>
        <form method="post" action="login.php" class="login-form">
            <p>
                <label>username</label>
                <input type="text" name="username" class="username-input"/>
            </p>
            <p>
                <label>password</label>
                <input type="password" name="password" class="password-input"/>
            </p>
            <p>
                <button type="submit" class="login-button">Submit</button>
            </p>
        </form>

<?php
    if ($_SERVER['REQUEST_METHOD'] == "POST") {
        require('connect.php');
        $stmt = $connection->prepare("SELECT COUNT(*) FROM User WHERE username=? AND password=?");
        $stmt->bind_param("ss", $_POST["username"], $_POST["password"]);
        $stmt->execute();
        $result = $stmt->get_result();
        $count = $result->fetch_row()[0];
        if ($count == 0) {
?>
            <div class="error">Invalid username or password</div>
<?php
        } else {
            setcookie("user", $_POST["username"], 0, "/");
            header("Location: /index.php");
        }
        $connection->close();
    }
?>

    </body>
</html>
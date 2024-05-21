<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Login | Grievances Portal</title>
    <link rel="stylesheet" href="styles/auth.css">
</head>
<body>
    <main>
        <h2>Login</h2>
        <form action="<?php echo htmlspecialchars($_SERVER["PHP_SELF"]) ?>" method="POST">
            <label for="username">Username</label>
            <input type="text" name="username" id="username" required>
            <label for="password">Password</label>
            <input type="password" name="password" id="password" required>
            <input type="submit" value="Login" />
        </form>
    </main>
</body>
<?php
function validateInput($data)
{
    $data = trim($data);
    $data = stripslashes($data);
    $data = htmlspecialchars($data);
    return $data;
}
if ($_POST["username"] != '') {
    $username = validateInput($_POST["username"]);
    $password = validateInput($_POST["password"]);
    if ($password != "admin" && $username != "admin") {
        echo "Error: Password incorrect.";
        die();
    } else {
        echo "Login successful!";
    }
    setcookie("user", serialize(array("username" => $username, "password" => $password, "userType" => "admin")), time() + 60 * 60, "/");
    if (count($_COOKIE) <= 0) {
        echo "Please enable the cookies.";
    } else {
        header("Location: grievances.php");
        die();
    }
}
?>
</html>
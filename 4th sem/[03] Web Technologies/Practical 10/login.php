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
    $conn = mysqli_connect("localhost", "root", "", "grievances");
    if (!$conn) {
        echo "Connection Failed!" . mysqli_connect_error();
        die();
    }
    $result = $conn->query("SELECT * FROM users JOIN user_type WHERE users.role = user_type.id AND username='" . $username . "';");
    if ($result->num_rows <= 0) {
        echo $row;
        echo "Error: User not found.";
        die();
    } else {
        $row = $result->fetch_assoc();
        if ($row["pwd"] != $password) {
            echo "Error: Password incorrect.";
            die();
        } else {
            echo "Login successful!";
        }
    }
    $conn->close();
    setcookie("user", serialize(array("username" => $username, "password" => $password, "userType" => $row["role"], "userId" => $row["id"])), time() + 60 * 60, "/");
    if (count($_COOKIE) <= 0) {
        echo "Please enable the cookies.";
    } else {
        header("Location: grievances.php");
        die();
    }
}
?>
</html>
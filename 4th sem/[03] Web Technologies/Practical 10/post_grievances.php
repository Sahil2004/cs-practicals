<?php
$conn = mysqli_connect("localhost", "root", "", "grievances");
if (!$conn) {
    echo "Connection Failed: " . mysqli_connect_error();
    die();
}
$user = unserialize($_COOKIE["user"]);
if (!$conn->query("INSERT INTO grievances VALUES ('" . $user["userId"] . "', '" . $user["username"] . "', " . "NULL, '" . $_POST["grievance_type"] . "', '" . $_POST["subject"] . "', '" . $_POST["description"] . "', '" . date("Y-m-d", time()) . "', NULL)")) {
    echo "Error: " . $conn->error;
    die();
} else {
    echo "Grievance posted successfully!";
}
$conn->close();
?>
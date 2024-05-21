<?php
session_start();
if (isset($_COOKIE["user"])) {
    $user = unserialize($_COOKIE["user"]);
    $_SESSION["username"] = $user["username"];
} else {
    header("Location: login.php");
    die();
}
?>
<!DOCTYPE html>
<html lang="en">

<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Grievances Dashboard</title>
    <link rel="stylesheet" href="styles/dashboard.css">
</head>

<body>
    <a href="logout.php">Logout</a>
    <?php
    if (unserialize($_COOKIE["user"])["userType"] === "Student") {
        echo '
    <h2>Grievance Form</h2>
    <form action="post_grievances.php" method="POST" onsubmit="validateGrievanceForm()">
        <label for="subject">Subject:</label><br />
        <input type="text" id="subject" name="subject" required /><br /><br />

        <label for="description">Description:</label><br />
        <textarea id="description" name="description" rows="4" required></textarea><br /><br />

        <label for="grievance_type">Grievance Type:</label><br />
        <select name="grievance_type" id="grievance_type">
            <option value="1">Miscellaneous</option>
            <option value="2">Academics</option>
            <option value="3">Admin Department</option>
            <option value="4">Online</option>
            <option value="5">Examination and Result</option>
            <option value="6">Canteen</option>
            <option value="7">Sports</option>
            <option value="8">Infrastructure</option>
            <option value="9">Ragging</option>
        </select>
        <br /><br />

        <label for="attachments">Attach any file:</label><br />
        <input type="file" name="attachments" id="attachments" /><br /><br />

        <input type="submit" value="Submit" />
    </form>
    ';
        echo "<section class='studentGrievances'><h1>Your Grievances:</h1></section>";
    } else {
        echo "<section class='grievances'><h1>Current Grievances:</h1></section>";
    }
    ?>
    <script src="scripts/grievances.js" defer async></script>
</body>

</html>
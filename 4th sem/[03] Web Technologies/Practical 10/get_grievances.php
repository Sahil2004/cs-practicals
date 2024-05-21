<?php
$query = $_REQUEST["q"];
$conn = mysqli_connect("localhost", "root", "", "grievances");
if (!$conn) {
    echo "Connection Failed!" . mysqli_connect_error();
    die();
}
if ($query === "user") {
    $grievances = $conn->query("SELECT * FROM grievances WHERE roll_no='" . unserialize($_COOKIE["user"])["username"] . "'");
} else {
    $grievances = $conn->query("SELECT * FROM grievances");
}
if ($grievances->num_rows > 0) {
    while ($row = $grievances->fetch_assoc()) {
        echo "<article class='grievance'>";
        echo "<h3>" . $row["subject"] . "</h3>";
        echo "<p>" . $row["description"] . "</p>";
        echo "<p><strong>Grievance Type:</strong> " . $row["grievance_type"] . "</p>";
        echo "<p><strong>Attachments:</strong> " . $row["attachments"] . "</p>";
        echo "</article>";
    }
}
$conn->close();
?>
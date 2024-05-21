<?php
setcookie("user", "", time() - 3600);
session_unset();
session_destroy();
?>
<html>
    <head>
        <script>
            window.location.href = "index.html";
        </script>
    </head>
</html>
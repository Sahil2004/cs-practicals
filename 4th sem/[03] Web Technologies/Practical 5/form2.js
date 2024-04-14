function validateUserRegistrationForm() {
	var username = document.getElementById("username").value;
	var password = document.getElementById("password").value;
	var role = document.getElementById("role").value;

	if (username === "" || password === "" || role === "") {
		alert("All fields are required!");
		return false;
	}
	if (password.length < 8) {
		alert("Password must be at least 8 characters long!");
		return false;
	}

	return true;
}

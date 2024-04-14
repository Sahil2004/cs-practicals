function validateAddUserTypeForm() {
	var name = document.getElementById("name").value;

	if (name.trim() === "") {
		alert("Please enter the user type name.");
		return false;
	}

	return true;
}

function validateRenameUserTypeForm() {
	var oldName = document.getElementById("old_name").value;
	var newName = document.getElementById("new_name").value;

	if (oldName.trim() === "") {
		alert("Please enter the old user type name.");
		return false;
	}

	if (newName.trim() === "") {
		alert("Please enter the new user type name.");
		return false;
	}

	return true;
}

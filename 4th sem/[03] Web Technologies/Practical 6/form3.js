function validateAddDepartmentForm() {
	var name = document.getElementById("name").value;

	if (name.trim() === "") {
		alert("Please enter the department name.");
		return false;
	}

	return true;
}

function validateRenameDepartmentForm() {
	var oldName = document.getElementById("old_name").value;
	var newName = document.getElementById("new_name").value;

	if (oldName.trim() === "") {
		alert("Please enter the old department name.");
		return false;
	}

	if (newName.trim() === "") {
		alert("Please enter the new department name.");
		return false;
	}

	return true;
}

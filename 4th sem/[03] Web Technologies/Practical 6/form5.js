function validateAddGrievanceTypeForm() {
	var name = document.getElementById("name").value;

	if (name.trim() === "") {
		alert("Please enter the grievance type name.");
		return false;
	}

	return true;
}

function validateRenameGrievanceTypeForm() {
	var oldName = document.getElementById("old_name").value;
	var newName = document.getElementById("new_name").value;

	if (oldName.trim() === "") {
		alert("Please enter the old grievance type name.");
		return false;
	}

	if (newName.trim() === "") {
		alert("Please enter the new grievance type name.");
		return false;
	}

	return true;
}

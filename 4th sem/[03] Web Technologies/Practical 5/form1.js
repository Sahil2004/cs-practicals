function validateGrievanceForm() {
	var rollNo = document.getElementById("roll_no").value;
	var subject = document.getElementById("subject").value;
	var description = document.getElementById("description").value;
	var grievanceType = document.getElementById("grievance_type").value;

	if (
		rollNo === "" ||
		subject === "" ||
		description === "" ||
		grievanceType === ""
	) {
		alert("All fields are required!");
		return false;
	}

	return true;
}

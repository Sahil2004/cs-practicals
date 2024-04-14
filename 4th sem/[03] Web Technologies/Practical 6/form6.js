// Function to validate Grievance Comment Form
function validateGrievanceCommentForm() {
	var grievanceId = document.getElementById("gid").value;
	var comment = document.getElementById("comment").value;

	if (grievanceId.trim() === "") {
		alert("Please enter the grievance ID.");
		return false;
	}

	if (isNaN(grievanceId)) {
		alert("Grievance ID must be a number.");
		return false;
	}

	if (comment.trim() === "") {
		alert("Please enter the grievance comment.");
		return false;
	}

	return true;
}

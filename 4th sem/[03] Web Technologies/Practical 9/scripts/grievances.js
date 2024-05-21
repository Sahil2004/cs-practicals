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

function showGrievances() {
	let doc = document.querySelector(".grievances");
	let sdoc = document.querySelector(".studentGrievances");
	let xhttp = new XMLHttpRequest();
	xhttp.onreadystatechange = function () {
		if (this.readyState === 4 && this.status === 200) {
			if (doc) doc.innerHTML += this.responseText;
			else sdoc.innerHTML += this.responseText;
		}
	};
	xhttp.open("GET", "get_grievances.php?q=user", true);
	xhttp.send();
}

window.onload = showGrievances();

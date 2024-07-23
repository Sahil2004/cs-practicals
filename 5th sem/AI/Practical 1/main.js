const canvas = document.getElementById("graphCanvas");

const ctx = canvas.getContext("2d");

let nodes = [];

let edges = [];

let isDrawingEdge = false;

let selectedNode = null;

canvas.addEventListener("mousedown", (e) => {
	const { offsetX, offsetY } = e;

	const node = findNode(offsetX, offsetY);

	if (node) {
		isDrawingEdge = true;

		selectedNode = node;
	} else {
		nodes.push({ x: offsetX, y: offsetY });

		drawGraph();
	}
});

canvas.addEventListener("mouseup", (e) => {
	if (isDrawingEdge) {
		const { offsetX, offsetY } = e;

		const node = findNode(offsetX, offsetY);

		if (node && node !== selectedNode) {
			edges.push({ from: selectedNode, to: node });
		}

		isDrawingEdge = false;

		selectedNode = null;

		drawGraph();
	}
});

function findNode(x, y) {
	return nodes.find((node) => Math.hypot(node.x - x, node.y - y) < 10);
}

function drawGraph() {
	ctx.clearRect(0, 0, canvas.width, canvas.height);

	edges.forEach(({ from, to }) => {
		ctx.beginPath();

		ctx.moveTo(from.x, from.y);

		ctx.lineTo(to.x, to.y);

		ctx.stroke();
	});

	nodes.forEach((node) => {
		ctx.beginPath();

		ctx.arc(node.x, node.y, 10, 0, Math.PI * 2);

		ctx.fill();
	});
}

function chooseTraversal(type) {
	if (type === "bfs") {
		bfs(nodes[0]);
	} else if (type === "dfs") {
		dfs(nodes[0]);
	}
}

function bfs(startNode) {
	let visited = new Set();

	let queue = [startNode];

	let index = 0;

	const interval = setInterval(() => {
		if (queue.length === 0) {
			clearInterval(interval);

			return;
		}

		const node = queue.shift();

		if (!visited.has(node)) {
			visited.add(node);

			animateNode(node);

			edges.forEach((edge) => {
				if (edge.from === node && !visited.has(edge.to)) {
					queue.push(edge.to);
				}

				if (edge.to === node && !visited.has(edge.from)) {
					queue.push(edge.from);
				}
			});
		}
	}, 1000);
}

function dfs(startNode) {
	let visited = new Set();

	let stack = [startNode];

	const interval = setInterval(() => {
		if (stack.length === 0) {
			clearInterval(interval);

			return;
		}

		const node = stack.pop();

		if (!visited.has(node)) {
			visited.add(node);

			animateNode(node);

			edges.forEach((edge) => {
				if (edge.from === node && !visited.has(edge.to)) {
					stack.push(edge.to);
				}

				if (edge.to === node && !visited.has(edge.from)) {
					stack.push(edge.from);
				}
			});
		}
	}, 1000);
}

function animateNode(node) {
	ctx.beginPath();

	ctx.arc(node.x, node.y, 15, 0, Math.PI * 2);

	ctx.fillStyle = "red";

	ctx.fill();

	setTimeout(() => {
		drawGraph();
	}, 500);
}

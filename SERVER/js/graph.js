	document.addEventListener("DOMContentLoaded", function(){
				// Create liteChart.js Object
				let d = new liteChart("chart");
				
				d.setLabels(data[0]);
				d.addLegend({"name": parametr, "stroke": "#3b95f7", "fill": "#fff", "values": data[1]});

				// Inject chart into DOM object
				let div = document.getElementById("object");
				d.inject(div);

				// Draw
				d.draw();
				document.getElementById('chart').style = "width: 90%; height: 65%;";
				d.draw();

				document.getElementById('chart-grid-x-4-label-mark-0').setAttribute("x1", 100);
				document.getElementById('chart-grid-x-4-label-mark-0').setAttribute("y1", 20);
				document.getElementById('chart-grid-x-4-label-mark-0').setAttribute("x2", 115);
				document.getElementById('chart-grid-x-4-label-mark-0').setAttribute("y2", 20);

				document.getElementById('chart-grid-x-4-label-text-0').setAttribute("x", 120);
				document.getElementById('chart-grid-x-4-label-text-0').setAttribute("y", 20);
			});
document.addEventListener("DOMContentLoaded", function(){
			// Создать объект графика
			let d = new liteChart("chart");
			
			d.setLabels(data[0]);
			d.addLegend({"name": parametr, "stroke": "#3b95f7", "fill": "#fff", "values": data[1]});

			// Поместить график внутрь элемнта
			let div = document.getElementById("object");
			d.inject(div);

			// Отрисовка
			d.draw();
			document.getElementById('chart').style = "width: 90%; height: 65%;";
			d.draw();

			let char_mark = document.getElementById('chart-grid-x-4-label-mark-0');
			char_mark.setAttribute("x1", 100);
			char_mark.setAttribute("y1", 20);
			char_mark.setAttribute("x2", 115);
			char_mark.setAttribute("y2", 20);

			let char_text = document.getElementById('chart-grid-x-4-label-text-0');
			char_text.setAttribute("x", 120);
			char_text.setAttribute("y", 20);
		});
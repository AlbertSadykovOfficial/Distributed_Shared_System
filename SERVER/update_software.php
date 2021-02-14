<!DOCTYPE html>
<html>
<head>
	<meta charset='UTF-8'>
	<title>ПО</title>
	<link rel="stylesheet" type="text/css" href="style/style.css">
	<link rel="stylesheet" type="text/css" href="style/table.css">
</head>
<body>

	<header>
		<span><a href="index.html">ПАО неФТЕБАЗА</a></span>
		<span></span>
		<span></span>
	</header>
	<main>
		<div style="font-size: 200%; text-align: center; margin-top: 20px;">Pool устройств</div>
			<table>
				<tbody>
					<tr>
						<td> Устройство </td>
						<td> IP-адрес</td>
						<td> Ссылка</td>
					</tr>
<?php
		if(($fp = fopen("reg_list.csv", "r")) !== FALSE)
		{
			while(($data = fgetcsv($fp, 0, ";")) !== FALSE)
			{
				echo "<tr>";
				echo "<td> ".$data[0]." </td>";
				echo "<td> ".$data[1]." </td>";
				echo "<td><a href='http://".$data[1]."/update'>Update</a> </td>";
				echo "</tr>";
			}
		}
		fclose($fp);
?>
				</tbody>
			</table>
		</main>
	</body>
</html>
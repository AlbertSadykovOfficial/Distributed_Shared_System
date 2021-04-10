<!DOCTYPE html>
<html>
<head>
	<meta charset='UTF-8'>
	<title>Показания</title>
	<link rel="stylesheet" type="text/css" href="style/style.css">
	<link rel="stylesheet" type="text/css" href="style/table.css">

	<script>
		let objects = [];
	</script>
</head>
<body>

	<header>
		<span><a href="index.html">ПАО неФТЕБАЗА</a></span>
		<span></span>
		<span></span>
	</header>
	<main>
		<div style="font-size: 200%; text-align: center; margin-top: 20px;">Объекты</div>
			<table style='width: 20%;'>
				<tbody>
<?php
		$count   = 0;
		$content = "";

									$data_dir = "storage";
									$dir = opendir($data_dir);

									while ($folder = readdir($dir))
									{
											if ($folder !== '.' && $folder !== '..')
											{
													$file_list = "<tr id='$folder'>";
													$tmp_dir = opendir($data_dir.'/'.$folder);

													while ($file = readdir($tmp_dir))
													{
															if ($file !== '.' && $file !== '..')
															{
																if (strpos($file, '.csv')) 
																{
																	$img = "img/graph.jpg";
																	//$href = " <a href='graph.php?object=$folder&sensor=$file'>$file</a>";
																	$href = " <a href='graph.php?".
																										"object=$folder".
																										"&sensor=$file'>".
																										$file.
																						"</a>";
																}else{
																	$img = "img/control.png";
																	$href = "control.php?object=$folder&device=$file&action";
																	$href = " $file ( <a href='$href=on'>On</a>".
																			" / <a href='$href=off'>Off</a>)";
																}

																$file_list = $file_list.
																"<tr><td>".
																		"<img src='$img'> ". $href.
																"</td></tr>";
															}
													}
													closedir($tmp_dir);

													$file_list = $file_list."</tr>";
													echo
														"<script>".
															"objects.push(\"".$file_list."\");".
														"</script>";
													$content = $content.
														"<tr onclick=open_folder($count,'$folder')><td>".
															"<img src='img/folder.png'> ".
															$folder.
														"</td></tr>";
													$count++;
											}
									}
									closedir($dir);

									//$content = $content;
									echo "<script>objects.push(\"".$content."\");</script>";
?>
				</tbody>
			</table>
		</main>
	</body>
<script>
	let tbody = document.getElementsByTagName('tbody')[0];
	tbody.innerHTML = "<tr><td>storage</td></tr>" + objects[objects.length-1];

	function open_folder(i, dir)
	{
		tbody.querySelector('tr').remove();
		tbody.innerHTML = "<tr><td>"+dir+"</td></tr>" + objects[i];

		if (dir !== 'storage')
		{
			html = "<tr>"+
									"<td onclick=open_folder(objects.length-1,\"storage\")>"+
										"BACK"+
									"</td>"+
							"</tr>";
			tbody.insertAdjacentHTML('beforeEnd', html);
		}
	}
</script>

</html>

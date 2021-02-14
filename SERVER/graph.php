<!DOCTYPE html>
<html>
<head>
	<meta charset='UTF-8'>
	<title>Показания</title>
	<link rel="stylesheet" type="text/css" href="style/style.css">
	<link rel="stylesheet" type="text/css" href="style/table.css">
</head>
<body>

	<header>
		<span><a href="index.html">ПАО неФТЕБАЗА</a></span>
	</header>

	<main>
		<div >Горьковская 13 >
		<script>
				let data = [[],[]] ;
				parametr = "NONE";	
		</script> 
<?php
			if(isset($_GET['object']) && isset($_GET['sensor']))
			{
					$period = $_GET['period'];
					echo $_GET['object']; echo " > "; echo $_GET['sensor']; echo "</div>";
					
					if(($fp = fopen('storage/'.$_GET['object'].'/'.$_GET['sensor'], "r")) !== FALSE)
					{		
							echo "<script> let parametr = \" ".$_GET['object']."\";</script>";
							$first_time = TRUE;
							while(($data = fgetcsv($fp, 0, ";")) !== FALSE)
							{
									if ($first_time == TRUE)
									{
										echo "<script>parametr += \" (".$data[0]." - \";</script>";
										$first_time = FALSE;
									}
									echo "<script>data[0].push(\"".substr($data[0],-5)."\");</script>";
									echo "<script>data[1].push(\"".$data[1]."\");</script>";
									$last_time = $data[0];
							}
							echo "<script>parametr += \" ".$last_time.") \";</script>";
					}
					fclose($fp);
			}
?>	
		<div id="object" style="display: flex; justify-content: center; height: 800px; "></div>
	</main>

		<script src="js/graph.js"></script>
		<script src="js/liteChart.min.js"></script>
</body>
</html>
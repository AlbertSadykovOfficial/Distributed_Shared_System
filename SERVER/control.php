<!DOCTYPE html>
<html>
<head>
	<meta charset='UTF-8'>
	<title></title>
	<link rel="stylesheet" type="text/css" href="style/style.css">
</head>
<body>

	<header>
		<span><a href="index.html">ПАО неФТЕБАЗА</a></span>
		<span></span>
		<span></span>
	</header>

	<main>
<?php
		if (isset($_GET['device']) && isset($_GET['action']))
		{
				if(($fp = fopen("reg_list.csv", "r")) !== FALSE)
				{ 
						while(($data = fgetcsv($fp, 0, ";")) !== FALSE)
						{
								if($data[0] == $_GET['device'])
								{
										fclose($fp);
										$ip = $data[1];
										if($_GET['action'] == "on")
										{	
											file_get_contents("http://".$ip."/gpio_ON");
											echo "Включено";
										}
										else if($_GET['action'] == "off")
										{
											print file_get_contents("http://".$ip."/gpio_OFF");
											echo "Выключено";
										}
										break;
								}
						}
				}	
		}
?>
	</main>
</body>
</html>
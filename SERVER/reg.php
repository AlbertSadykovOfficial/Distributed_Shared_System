<?php
$client		= @$_SERVER['HTTP_CLIENT_IP'];
$forward	= @$_SERVER['HTTP_X_FORWARDED_FOR'];
$remote 	= @$_SERVER['REMOTE_ADDR'];

if (filter_var($client, FILTER_VALIDATE_IP)) $ip = $client;
elseif (filter_var( $forward, FILTER_VALIDATE_IP)) $ip =  $forward;
else $ip =  $remote;
echo $ip;

if(isset($_GET['object']) && isset($_GET['id']))
{
		$list = [];
		$is_new = true;
		if(($fp = fopen("reg_list.csv", "r")) !== FALSE)
		{
				while(($data = fgetcsv($fp, 0, ";")) !== FALSE)
				{
						if($data[0] == $_GET['id'])
						{
								$is_new = false;
								$data[1] = $ip;
								echo "ip have changed";
						}
						$list[] = $data;
				}
		}
		fclose($fp);
			
		$dir = "storage/".$_GET['object'];
		if ($is_new)
		{
				$list[] = array($_GET['id'], $ip);
				
				if (!file_exists($dir)){
					mkdir($dir, 0777);
				}
				
		}
		
		$fp = fopen("reg_list.csv", "w");
		foreach($list as $fields)
		{
				fputcsv($fp, $fields, ';', '"');
		}
		fclose($fp);

		$fp = fopen($dir.'/'.$_GET['id'],"w");
		fwrite($ip);
		fclose($fp);
			
}
	
?>
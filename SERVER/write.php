<?php

if(isset($_GET['object']) && isset($_GET['sensor']) && isset($_GET['data']))
{
	$dir = 'storage/'.$_GET['object'];
	if (!file_exists($dir)){
			mkdir($dir, 0777);
	}
	$filename = $dir.'/'.$_GET['sensor'].'.csv';
	$filestream = fopen($filename, 'a') or die('faild');

	fwrite($filestream, date('d-m-y h:i:s').";".$_GET['data']."\n");

	fclose($filestream);
}
?>

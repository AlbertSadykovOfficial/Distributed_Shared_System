<?php

	if(isset($_POST['object']) && isset($_POST['sensor']) && isset($_POST['data']))
	{
		$filename = 'storage/'.$_POST['object'].'/'.$_POST['sensor'].'.csv';
		$filestream = fopen($filename, 'a') or die('faild');

		fwrite($filestream, $_POST['data']);
			
		fclose($filestream);
	}
?>

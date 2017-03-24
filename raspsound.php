<?php
$data = $_POST['data'];
$today=date("Y-m-d H:i:s    "); //timestamp of this reception
$record= $today . "," . $data ."\n";

$file ="sound.log"; //specify the file name
if(file_exists($file))
	$fp=fopen($file,"a"); //open the file in appending mode
else
	$fp=fopen($file,"w"); //else open the file in writing mode
fwrite($fp,$record); //write record to the file
fclose($fp);
//echo "data stored\n";
?>
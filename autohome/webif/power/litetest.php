<?php

$dbhandle = sqlite_open('../liteadmin/weather', 0666, $error);
if (!$dbhandle) die ($error);
//$output .= $error;
$stm = "SELECT * FROM data";
$ok = sqlite_query($dbhandle, $stm);

if (!$ok)
   die("Cannot execute query. $error");

$row = sqlite_fetch_array($result, SQLITE_ASSOC); 
$output .= print_r($row);
$output .= echo "<br>";
//$output .=  "test";
//$output .= "<br>";
//$output .= "<br>";
//$output .= "test2";
sqlite_close($dbhandle);
?>

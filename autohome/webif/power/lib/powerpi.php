<?php
define('POWERPIPORT', 6677);

$action = Get('action');

switch($action) {
	
	/* ------------------- Socket ------------------- */
	case 'setsocket':
		$socket = Get('socket');
    $status = Get('status');
		
		if($socket != '' && $status != '')
			Send("setsocket:$socket:$status");
	break;

	case 'addsocket':
		$name = Get('name');
    $code = Get('code');

		if($name != '' && $code != '')
			Send("addsocket:$name:$code");

	break;

	case 'deletesocket':
  	$socket = Get('socket');
		
		if($socket!='')
			Send("delsocket:$socket");
	break;


	/* ------------------- Gpio ------------------- */

	case 'setgpio':
		$gpio = Get('gpio');
    $status = Get('status');

		if($gpio != '' && $status != '')
      Send("setgpio:$gpio:$status");
	break;	

	case 'addgpio':
    $name = Get('name');
    $gpio = Get('gpio');

		if($name != '' && $gpio != '')
      Send("addgpio:$name:$gpio");
	break;

	case 'deletegpio':
    $gpio = Get('gpio');
	
		if($gpio != '')
      Send("delgpio:$gpio");
	break;

/* ------------------- Wetter ------------------- */

	case 'setwetter':
		$gpio = Get('gpio');
    $status = Get('status');

		if($gpio != '' && $status != '')
      Send("setgpio:$gpio:$status");
	break;	
case 'newwetter':

break;


	case 'addwetter':
    $name = Get('name');
    $chan = Get('chan');
    $sender =GET('sender');

		if($name != '' && $chan != '')
      $db = new PDO($this->app->Conf->DB_FILE);
$db->setAttribute(PDO::ATTR_ERRMODE,
                 PDO::ERRMODE_EXCEPTION);
                 $exec='INSERT INTO location ("key","name","sender_id","channel_id") VALUES (NULL,"'.$name.'","'.$sender.'","'.$chan.'")';
$db->exec($exec);
$db = null;

	break;

	case 'deletewetter':
    $name = Get('name');
	
			
$db = new PDO($this->app->Conf->DB_FILE);
$db->setAttribute(PDO::ATTR_ERRMODE,
                 PDO::ERRMODE_EXCEPTION);
                 $exec='DELETE FROM location WHERE name = "'.$name.'"';
$db->exec($exec);
$db = null;
	
     
	break;

	/* ------------------- Schedule ------------------- */

	case 'setschedule':
    $schedule = Get('schedule');

    if($schedule != '')
      Send("setschedule:$schedule");
  break;

	case 'addschedule':
		$name = Get('name');
		$socket = Get('socket');
    $gpio = Get('gpio');
    $hour = Get('hour');
    $minute = Get('minute');
    $onoff = Get('onoff');

		if($name != '' && ($socket != '' || $gpio!= '') && $hour != '' && $minute != '' && $onoff != '')
			Send("addschedule:$name:$socket:$gpio:$hour:$minute:$onoff:1");

	break;

  case 'deleteschedule':
    $schedule = Get('schedule');

		if($schedule != '')
      Send("delschedule:$schedule");
	break;
}

/* ===================== Functions ===================== */

function Get($val) {
	if(isset($_GET[$val]))
		return $_GET[$val];
}

function StartsWith($Haystack, $Needle){
    return strpos($Haystack, $Needle) === 0;
}

function GetValues($data, $type) {
	$lines = explode(';', $data);

	$values = array();
  for($i=0;$i<count($lines);$i++) {
    if(StartsWith($lines[$i], $type)) {
      $values[] = explode(':', $lines[$i]);
    }
  }
	return $values;
}

function Send($data) {
	$socket = fsockopen('udp://127.0.0.1', POWERPIPORT, $errno, $errstr, 10);
	$out = "";
  if(!$socket) {
  	echo "$errstr ($errno)";
    exit;
  } else {
		fwrite($socket, "$data");
		$out = fread($socket, 20000);
		fclose($socket);
	}
 
	return $out;
}

function GetData() {
	return Send("list:all");
}

function ParseSockets($data) {
	$values = GetValues($data, 'socket:');

	$sockets = array();
	for($i=0; $i < count($values); $i++) {
		$sockets[] = array('name'=>trim($values[$i][1]), 'code'=>trim($values[$i][2]));
	}

	return $sockets;
}

function ParseGpios($data) {
  $values = GetValues($data, 'gpio:');

  $gpios = array();
  for($i=0; $i < count($values); $i++) {
    $gpios[] = array('name'=>trim($values[$i][1]), 'gpio'=>trim($values[$i][2]));
  }

  return $gpios;
}

function ParseSchedules($data) {
  $values = GetValues($data, 'schedule:');

  $schedules = array();
  for($i=0; $i < count($values); $i++) {
  	$schedules[] = array('name'=>trim($values[$i][1]), 'socket'=>trim($values[$i][2]), 'gpio'=>trim($values[$i][3]), 'hour'=>trim($values[$i][4]),
              'minute'=>trim($values[$i][5]), 'onoff'=>trim($values[$i][6]), 'status'=>trim($values[$i][7]));
	}

  return $schedules;
}
?>

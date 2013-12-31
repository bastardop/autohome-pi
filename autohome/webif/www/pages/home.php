<?php

class Home
{
  var $app;
  
  function Home(&$app)
  {
    $this->app = $app;

    $this->app->Nav->AddPage('home');
    $this->app->Nav->AddAction('list', 'HomeList');
    $this->app->Nav->AddAction('weather', 'HomeWeather');
    $this->app->Nav->AddAction('settings', 'HomeSettings');
    $this->app->Nav->AddAction('help', 'HomeHelp');
    $this->app->Nav->DefaultAction('list');
  }

  function HomeList()
  {
    include('./lib/powerpi.php');

		$data = GetData();   
    
		// ### Sockets ###
    $sockets = ParseSockets($data);
    $sockets_out = '';
    for($i=0;$i<count($sockets);$i++) {
      $sockets_out .= "<li>
                        <div class=\"button socket\">
                          <div class=\"button_text\">{$sockets[$i]['name']}</div>
                          <div class=\"button_off\" socket-name=\"{$sockets[$i]['name']}\">OFF</div>
                          <div class=\"button_on\" socket-name=\"{$sockets[$i]['name']}\">ON</div> 
                        </div>
                       </li>";
    }
    $sockets_out = ((count($sockets) > 0) ? "<ul class=\"buttonlist\">{$sockets_out}</ul>" : '');
    $this->app->Tpl->Set('SOCKETS', $sockets_out);


    // ### GPIO'S ###
    $gpios = ParseGpios($data);
    $gpios_out = '';
    for($i=0;$i<count($gpios);$i++) {
      $gpios_out .= "<li>
                      <div class=\"button gpio\">
                          <div class=\"button_text\">{$gpios[$i]['name']}</div>
                          <div class=\"button_off\" gpio-name=\"{$gpios[$i]['name']}\">OFF</div>
                          <div class=\"button_on\" gpio-name=\"{$gpios[$i]['name']}\">ON</div> 
                        </div>
                      </li>";
    }
    $gpios_out = ((count($gpios) > 0) ? "<ul class=\"buttonlist\">{$gpios_out}</ul>" : '');
    $this->app->Tpl->Set('GPIOS', $gpios_out);
		
		// ### Schedules ###
		$schedules = ParseSchedules($data);
    $schedules_out = '';
    for($i=0;$i<count($schedules);$i++) {

			$status_text = (($schedules[$i]['status']=='1') ? 'Active' : 'Inactive');

      $schedules_out .= "<li>
                      <div class=\"button schedule\" schedule-name=\"{$schedules[$i]['name']}\">
                          <div class=\"button_text\">{$schedules[$i]['name']}</div>
                          <div class=\"status\">$status_text</div>
                        </div>
                      </li>";
    }
    $schedules_out = ((count($schedules) > 0) ? "<ul class=\"buttonlist\">{$schedules_out}</ul>" : '');
    $this->app->Tpl->Set('SCHEDULES', $schedules_out);

    
    $this->app->Tpl->Set('MENUHOME', 'class="active"');
    $this->app->Tpl->Parse('PAGE', 'home_list.tpl');
  }
  
  function HomeSettings()
  {
    include('./lib/powerpi.php');
 
		$data = GetData();
 
    // ### Sockets ###
    $sockets = ParseSockets($data);
    $socket_table = '';
    for($i=0;$i<count($sockets);$i++) {
      $socket_table .= "<tr><td>{$sockets[$i]['name']}</td>
                        <td>{$sockets[$i]['code']}</td>
                        <td><a socket-name=\"{$sockets[$i]['name']}\" socket-code=\"{$sockets[$i]['code']}\" href=\"#\" class=\"socket_delete btn btn-large btn-block btn-danger\" style=\"float:none;\"><span class=\"fui-cross-16\"></span></a></td></tr>";
    }
    $this->app->Tpl->Set('SOCKETTABLE', $socket_table);
    
    
    // ### GPIO'S ###
    $gpios = ParseGpios($data);
    $gpio_table = '';
    for($i=0;$i<count($gpios);$i++) {
      $gpio_table .= "<tr><td>{$gpios[$i]['name']}</td>
                        <td>{$gpios[$i]['gpio']}</td>
                        <td><a gpio-name=\"{$gpios[$i]['name']}\" gpio-id=\"{$gpios[$i]['gpio']}\" href=\"#\" class=\"gpio_delete btn btn-large btn-block btn-danger\" style=\"float:none;\"><span class=\"fui-cross-16\"></span></a></td></tr>";
    }
    $this->app->Tpl->Set('GPIOTABLE', $gpio_table);

// ### WETTER Settings ###
try {
$db = new PDO('sqlite:/var/www/liteadmin/weather');
$db->setAttribute(PDO::ATTR_ERRMODE,
                 PDO::ERRMODE_EXCEPTION);
$result = $db->query('SELECT * FROM location');


   $weather_table .= '';
    foreach($result as $row) {
      $weather_table .= "<tr><td>{$row['name']}</td>
                        <td>{$row['sender_id']}</td>
			<td>{$row['channel_id']}</td></tr>";
                      }
   // $weather_out = "<ul class=\"buttonlist\">{$weather_out}</ul>";

$db = null;
}
catch(PDOException $e) {
$weater_table = $e->getMessage();
}
  $this->app->Tpl->Set('WEATHERTABLE', $weather_table);
    
    // ### Scheduler ###
    $schedules = ParseSchedules($data);
    $schedule_table = '';
    for($i=0;$i<count($schedules);$i++) {
      $onoff_text = (($schedules[$i]['onoff']=='1') ? 'ON' : 'OFF');
      $socket_notfound = (($schedules[$i]['socket']=='' || $this->app->Core->ArraySearch('name', $schedules[$i]['socket'], $sockets)) 
				? '' : '<span class="notfound">[Not Found]</span>');
      $gpio_notfound = (($schedules[$i]['gpio']=='' || $this->app->Core->ArraySearch('name', $schedules[$i]['gpio'], $gpios)) 
				? '' : '<span class="notfound">[Not Found]</span>');
      $schedule_table .= "<tr>
													<td>{$schedules[$i]['name']}</td>
													<td>{$schedules[$i]['socket']} $socket_notfound</td>
                          <td>{$schedules[$i]['gpio']} $gpio_notfound</td>
                          <td>".str_pad($schedules[$i]['hour'], 2, 0, STR_PAD_LEFT).":".str_pad($schedules[$i]['minute'], 2, 0, STR_PAD_LEFT)."</td>
                          <td>$onoff_text</td>
                        <td><a schedule-name=\"{$schedules[$i]['name']}\" schedule-socket=\"{$schedules[$i]['socket']}\" schedule-gpio=\"{$schedules[$i]['gpio']}\" schedule-hour=\"{$schedules[$i]['hour']}\" schedule-minute=\"{$schedules[$i]['minute']}\" schedule-onoff=\"{$schedules[$i]['onoff']}\" href=\"#\" class=\"schedule_delete btn btn-large btn-block btn-danger\" style=\"float:none;\"><span class=\"fui-cross-16\"></span></a></td></tr>";
    }
    $this->app->Tpl->Set('SCHEDULERTABLE', $schedule_table);
    
    
    $gpio_select = $this->app->Core->ParseSelect($gpios, 'Choose GPIO');
    $this->app->Tpl->Set('GPIOSELECT', $gpio_select);
    
    $socket_select = $this->app->Core->ParseSelect($sockets, 'Choose Socket');
    $this->app->Tpl->Set('SOCKETSELECT', $socket_select);
    
    $hour_select = $this->app->Core->TimeSelect(23);
    $this->app->Tpl->Set('HOURSELECT', $hour_select);
    
    $minute_select = $this->app->Core->TimeSelect(59);
    $this->app->Tpl->Set('MINUTESELECT', $minute_select);
   

		$this->app->Tpl->Set('TIME', exec('date +"%T"'));
 
    $this->app->Tpl->Set('MENUSETTINGS', 'class="active"');
    $this->app->Tpl->Parse('PAGE', 'home_settings.tpl');
  }
   // ### HELP ###
  function HomeHelp()
  {
    
    $this->app->Tpl->Set('MENUHELP', 'class="active"');
    $this->app->Tpl->Parse('PAGE', 'home_help.tpl');
  }
    // ### WEATHER ###
  function HomeWeather()
  {

try {
$db = new PDO('sqlite:/var/www/liteadmin/weather');
$db->setAttribute(PDO::ATTR_ERRMODE,
                  PDO::ERRMODE_EXCEPTION);
$places = $db->query('SELECT * FROM location');

foreach($places as $place) {


$result = $db->query('SELECT * FROM data WHERE sender_id ='.$place['sender_id'].' AND channel_id='.$place['channel_id'].' ORDER BY key DESC LIMIT 1');

    $weather_out .= '';
    foreach($result as $row) {
      $weather_out .= "<li>
                        <div class=\"button socket\">
                          <div class=\"button_text\">{$place['name']}</div>                          
			 <div class=\"humi\" >{$row['humi']}%</div>
			  <div class=\"temp\" >{$row['temp']}° </div>
                           
                        </div>
                       </li>";
    }}
$pitemp = shell_exec('vcgencmd measure_temp');
$pitemp = substr($pitemp, 5,4);
 $weather_out .= "<li>
                        <div class=\"button socket\">
                          <div class=\"button_text\">Pi CPU</div>                          
                         
                          <div class=\"temp\" >{$pitemp}° </div>
                           
                        </div>
                       </li>";


    $weather_out = "<ul class=\"buttonlist\">{$weather_out}</ul>";

$db = null;
}
catch(PDOException $e) {
$weater_out = $e->getMessage();
}

$this->app->Tpl->Set('WEATHER', $weather_out);

    $this->app->Tpl->Set('MENUWEATHER', 'class="active"');
    $this->app->Tpl->Parse('PAGE', 'home_weather.tpl');
  }

  
}
?>

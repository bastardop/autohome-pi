<script>
$(document).ready(function() {

  // ### Sockets ###
  $('#socket_submit').click(function(){
    var name = $('#socket_name').val();
    var code = $('#socket_code').val();
  
    if(name=='' || code=='') {
      alert('Please enter name and socket');
      return;
    }
    
    $.get('[BASEDIR]/lib/powerpi.php?action=addsocket&name='+name+'&code='+code, function() {
      window.location.reload();
    });
  });

  $('.socket_delete').click(function(){
    var name = $(this).attr('socket-name');
    
    if(name=='') {
      alert('Socket information incomplete');
      return;
    }
    if(confirm('Sure?')) {
      $.get('[BASEDIR]/lib/powerpi.php?action=deletesocket&socket='+name, function() {
        window.location.reload();
      });
    }
  });

  // ### GPIOS ###
  $('#gpio_submit').click(function(){
    var name = $('#gpio_name').val();
    var gpio = $('#gpio_id option:selected').val();
   
    if(name=='' || gpio=='') {
      alert('Please enter name and choose gpio');
      return;
    }
    
    $.get('[BASEDIR]/lib/powerpi.php?action=addgpio&name='+name+'&gpio='+gpio, function() {
      window.location.reload();
    });
  });
  
  $('.gpio_delete').click(function(){
    var name = $(this).attr('gpio-name');
    var id = $(this).attr('gpio-id');
    
    if(name=='' || id=='') {
      alert('Gpio information incomplete');
      return;
    }
    if(confirm('Sure?')) {
      $.get('[BASEDIR]/lib/powerpi.php?action=deletegpio&gpio='+name+'&pin='+id, function() {
        window.location.reload();
      });
    }
  });
    
    // ### Wetter ###
  $('#wetter_submit').click(function(){
    var name = $('#wetter_name').val();
    var chan = $('#channel_id').val();
    var sender = $('#sender_id').val();
   
    if(name=='' || chan=='' || sender=='') {
      alert('Please enter name and choose gpio');
      return;
    }
    
    $.get('[BASEDIR]/lib/powerpi.php?action=addwetter&name='+name+'&chan='+chan+'&sender='+sender, function() {
      window.location.reload();
    });
  });
  
  $('#wetter_new').click(function(){
  
    $.get('[BASEDIR]/lib/powerpi.php?action=newwetter', function() {
      window.location.reload();
    });
  });
  
  
  $('.wetter_delete').click(function(){
    var name = $(this).attr('wetter-name');
    var id = $(this).attr('wetter-id');
    
    if(name=='' || id=='') {
      alert('wetter information incomplete');
      return;
    }
    if(confirm("Sure? "+name+"bla")) {
      $.get('[BASEDIR]/lib/powerpi.php?action=deletewetter&name='+name, function() {
        window.location.reload();
      });
    }
  });
  
  // ### Scheduler ###
  $('#schedule_submit').click(function(){

    var name = $('#schedule_name').val();
    var socket = $('#schedule_socket option:selected').val();
    var gpio = $('#schedule_gpio option:selected').val();
    var hour = $('#schedule_hour option:selected').val();
    var minute = $('#schedule_minute option:selected').val();
    var onoff = $('#schedule_onoff option:selected').val();
    
		if(name=='') {
			alert('Please enter a name');
			return;
		}

    if(socket=='' && gpio=='') {
      alert('Please choose a socket and/or gpio');
      return;
    }
    
    $.get('[BASEDIR]/lib/powerpi.php?action=addschedule&name='+name+'&socket='+socket+'&gpio='+gpio+'&hour='+hour+'&minute='+minute+'&onoff='+onoff, function() {
      window.location.reload();
    });
  });  

  $('.schedule_delete').click(function(){
    var name = $(this).attr('schedule-name');
    
    if(name=='') {
      alert('Schedule information incomplete');
      return;
    }
    if(confirm('Sure?')) {
      $.get('[BASEDIR]/lib/powerpi.php?action=deleteschedule&schedule='+name, function() {
        window.location.reload();
      });
    }
  });

});


</script>
[SCRIPT2]

  <div class="container-fluid">
    <h1>Settings</h1>
    <h3 class="demo-panel-title">Wireless sockets</h3>
    <table class="table table-bordered table-striped font-big" id="no-more-tables">
    <thead>
		  <tr>
		    <th>Name</th>
		    <th>Code (e.g. 11001A)</th>
		    <th class="span2"></th>
		  </tr>
		</thead>
    <tbody>
      [SOCKETTABLE]
     
      <tr> 
        <td class="add center"><input id="socket_name" type="text" value="" placeholder="Name" class="span3 nomargb fullwidth"></td>
        <td class="add center"><input id="socket_code" type="text" value="" placeholder="Code (e.g. 11001A)" class="span3 nomargb"></td>
        <td class="add center"><a id="socket_submit" href="#" class="btn btn-large btn-block btn-primary" style="float:none;">Add</a></td>
      </tr>
    </tbody>
    </table>
    
    <h3 class="demo-panel-title">GPIO's</h3>
    <table class="table table-bordered table-striped font-big" id="no-more-tables">
    <thead>
		  <tr>
		    <th>Name</th>
		    <th>GPIO</th>
		    <th class="span2"></th>
		  </tr>
		</thead>
    <tbody>
      [GPIOTABLE]
      <tr> 
        <td class="add center"><input id="gpio_name" type="text" value="" placeholder="Name" class="span3 nomargb fullwidth"></td>
        <td class="add center">
        <select name="gpio_id" id="gpio_id">
            <option value="2">GPIO 2</option>
            <option value="3">GPIO 3</option>
            <option value="4">GPIO 4</option>
            <option value="7">GPIO 7</option>
            <option value="8">GPIO 8</option>
            <option value="9">GPIO 9</option>
            <option value="10">GPIO 10</option>
            <option value="11">GPIO 11</option>
            <option value="14">GPIO 14</option>
            <option value="15">GPIO 15</option>
            <option value="17">GPIO 17</option>
            <option value="18">GPIO 18</option>
            <option value="22">GPIO 22</option>
            <option value="23">GPIO 23</option>
            <option value="24">GPIO 24</option>
            <option value="25">GPIO 25</option>
            <option value="27">GPIO 27</option>
            <option value="28">GPIO 28</option>
            <option value="29">GPIO 29</option>
            <option value="30">GPIO 30</option>
            <option value="31">GPIO 31</option>
          </select>
        </td>
        <td class="add center"><a id="gpio_submit" href="#" class="btn btn-large btn-block btn-primary" style="float:none;">Add</a></td>
      </tr>
    </tbody>
    </table>

 <h3 class="demo-panel-title">Wetter</h3>
    <table class="table table-bordered table-striped font-big" id="no-more-tables">
    <thead>
                  <tr>
                    <th>Name</th>
                    <th>Sender ID</th>
                   <th>Channel ID</th>
		    <th class="span2"></th>
                  </tr>
                </thead>
    <tbody>
      [WEATHERTABLE]
       <tr> 
        <td class="add center"><input id="wetter_name" type="text" value="" placeholder="Name" class="span3 nomargb fullwidth"></td>
        <td class="add center"><input id="sender_id" type="text" value="" placeholder="Sender ID" class="span3 nomargb"></td>
        <td class="add center"><input id="channel_id" type="text" value="" placeholder="Channel ID (0 für DHT)" class="span3 nomargb"></td>
        <td class="add center"><a id="wetter_submit" href="#" class="btn btn-large btn-block btn-primary" style="float:none;">Add</a></td>
      </tr>
       <tr> 
        <td class="add center"></td>
        <td class="add center">Sender ID für DHT ist Dreistellig</td>
        <td class="add center">Neue Funksender Anzeigen -></td>
        <td class="add center"><a id="wetter_new" href="index.php?page=home&action=settings&wetter=new" class="btn btn-large btn-block btn-primary" style="float:none;"> List New</a></td>
      </tr>
</tbody>
</table>

    
    <h3 class="demo-panel-title">Scheduler</h3>
    <table class="table table-bordered table-striped font-big" id="no-more-tables">
    <thead>
		  <tr>
		    <th>Name</th>
		    <th>Socket</th>
		    <th>GPIO</th>
        <th>Time (Now: [TIME])</th>
		    <th>On/Off</th>
        <th class="span2"></th>
		  </tr>
		</thead>
    <tbody>
      [SCHEDULERTABLE]
      <tr>
				<td class="add center">
					<input id="schedule_name" type="text" value="" placeholder="Name" class="span3 nomargb fullwidth">
				</td> 
        <td class="add center">
          <select id="schedule_socket" class="select-block span3">
          [SOCKETSELECT]
          </select>
        </td>
        <td class="add center">
          <select id="schedule_gpio" class="select-block span3">
          [GPIOSELECT]
          </select>
        </td>
        <td class="add center">
          <select id="schedule_hour" class="select-block span2">
          [HOURSELECT]
          </select>
          <select id="schedule_minute" class="select-block span2">
          [MINUTESELECT]
          </select>
        </td>
        <td class="add center">
          <select id="schedule_onoff" class="select-block span2">
            <option value="1">ON</option>
            <option value="0">OFF</option>
          <select>
        </td>
        <td class="add center"><a id="schedule_submit" href="#" class="btn btn-large btn-block btn-primary" style="float:none;">Add</a></td>
      </tr>
    </tbody>
    </table>
  </div>

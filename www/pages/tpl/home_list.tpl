<script>
$(document).ready(function() {
  $('.socket > .button_on').click(function() {
    var socket = $(this).attr('socket-name');
    if(socket!='' && socket!='undefined') {
      $.get('[BASEDIR]/lib/powerpi.php?action=setsocket&socket='+socket+'&status=1', function() {
      });
    }
  });
  
  $('.socket > .button_off').click(function() {
    var socket = $(this).attr('socket-name');
    if(socket!='' && socket!='undefined') {
      $.get('[BASEDIR]/lib/powerpi.php?action=setsocket&socket='+socket+'&status=0', function() {
      });
    }
  });
  
  $('.gpio > .button_on').click(function() {
    var gpio = $(this).attr('gpio-name');
    if(gpio!='' && gpio!='undefined') {
      $.get('[BASEDIR]/lib/powerpi.php?action=setgpio&gpio='+gpio+'&status=1', function() {
      });
    }
  });
  
  $('.gpio > .button_off').click(function() {
    var gpio = $(this).attr('gpio-name');
    if(gpio!='' && gpio!='undefined') {
      $.get('[BASEDIR]/lib/powerpi.php?action=setgpio&gpio='+gpio+'&status=0', function() {
      });
    }
  });

	$('.schedule').click(function() {
    var schedule = $(this).attr('schedule-name');
    if(schedule!='' && schedule!='undefined') {
      $.get('[BASEDIR]/lib/powerpi.php?action=setschedule&schedule='+schedule, function() {
				window.location.reload();
      });
    }
  });
});
</script>


<div class="container-fluid">
  [SOCKETS]
  [GPIOS]
 	[SCHEDULES] 
</div>

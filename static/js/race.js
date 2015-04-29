	var enable_acc = false;
	var max_acc_cycles = 20;
	var acc_cycles = 0;
	var acc_cycles_total_x = 0;
	var acc_cycles_total_y = 0;

	function init()
	{
		if (window.DeviceMotionEvent == undefined) {
        //No accelerometer is present. Use buttons. 
        alert("no accelerometer");
    }
    else {
        window.addEventListener("deviceorientation", accelerometerUpdate, true);
    }

    draw(0);

    $("input[name=radios]:radio").change(function () {
    	console.log("radio")

    	if ($("#turn_left").attr("checked"))
    	{
    		console.log("left");
    	}
    	else if ($("#turn_center").attr("checked"))
    	{
    		console.log("center");

    	}
    	else if ($("#turn_right").attr("checked"))
    	{
    		console.log("right");

    	}
    });


	}

   function accelerometerUpdate(event) {

	   if (!enable_acc) {return;};
     var x = event.beta;
     var y = event.gamma;
     if (x > 90) {x = 90};
     if (x < -90) {x = -90};

     x += 90;
     y += 90;

     x = x / 180;
     y = y / 180;

     x = (.5 - x) * 500;
     y = (y - .5) * 500;

     if (x > 60) {x = 60};
     if (x < -60) {x = -60};
     
     if (y > 50) 
     {
     	y = 100
     }
     else if (y < -50) 
     	{
     		y = -100
     	}
     else 
     	{
     		y=0
     	}

     if (acc_cycles < max_acc_cycles)
     {
     	acc_cycles_total_x += x;
     	acc_cycles_total_y += y;
     	acc_cycles++;
     }
     else
     {
     	x = Math.trunc(acc_cycles_total_x/acc_cycles);
     	y = Math.trunc(acc_cycles_total_y/acc_cycles);

      throttle(x);
      steering(y);

      if (y > 0) {document.getElementById("turn_right").checked = true;}
      else if (y < 0) {document.getElementById("turn_left").checked = true;}
      else if (y == 0) {document.getElementById("turn_forward").checked = true;}


	    document.querySelector('#acc_x').value = "X - " + x;
	    document.querySelector('#acc_y').value = "Y - " + y;

	    acc_cycles_total_x = 0;
     	acc_cycles_total_y = 0;
     	acc_cycles = 0;
     }
	 
	 }



	function draw(speed)
	{
      var  canvas = document.getElementById("speedometer");
      var  context = canvas.getContext("2d");
      context.clearRect(0,0,canvas.width, canvas.height);
      var centerX = canvas.width / 2;
      var centerY = canvas.height / 2;
      var radius = canvas.height / 2 - 20;

      context.beginPath();
      context.arc(centerX, centerY, radius, Math.PI*0.10, Math.PI*-1.1, true);

      var gradience = context.createRadialGradient(centerX, centerY, radius-radius/2, centerX, centerY, radius-radius/8);
       gradience.addColorStop(0, '#ff9000');
       gradience.addColorStop(1, '#000000');

       context.fillStyle = gradience;
       context.fill();
       context.closePath();
       context.restore();

	context.beginPath();
	context.strokeStyle = '#ffff00';
	context.translate(centerX,centerY);
	var increment = 2;
	context.font="15px Helvetica";
	for (var i=-18; i<=18; i++)
	{
		angle = Math.PI/30*i;
		sineAngle = Math.sin(angle);
		cosAngle = -Math.cos(angle);

		if (i % 5 == 0) {
		context.lineWidth = 8;
		iPointX = sineAngle *(radius -radius/4);
		iPointY = cosAngle *(radius -radius/4);
		oPointX = sineAngle *(radius -radius/7);
		oPointY = cosAngle *(radius -radius/7);

		wPointX = sineAngle *(radius -radius/2.5);
		wPointY = cosAngle *(radius -radius/2.5);
		context.fillText((i+18)*increment,wPointX-2,wPointY+4);
		}
		else
		{
		context.lineWidth = 2; 			
		iPointX = sineAngle *(radius -radius/5.5);
		iPointY = cosAngle *(radius -radius/5.5);
		oPointX = sineAngle *(radius -radius/7);
		oPointY = cosAngle *(radius -radius/7);
		}
		context.beginPath();
		context.moveTo(iPointX,iPointY);
		context.lineTo(oPointX,oPointY);
		context.stroke();
		context.closePath();
	}
	var numOfSegments = speed/increment;
	numOfSegments = numOfSegments -18;
	angle = Math.PI/30*numOfSegments;
	sineAngle = Math.sin(angle);
	cosAngle = -Math.cos(angle);
	pointX = sineAngle *(3/4*radius);
	pointY = cosAngle *(3/4*radius);

	context.beginPath();
	context.strokeStyle = '#000000';
	context.arc(0, 0, 19, 0, 2*Math.PI, true);
	context.fill();
        context.closePath();

	context.beginPath();    	
	context.lineWidth=6;
	context.moveTo(0,0);
        context.lineTo(pointX,pointY);
        context.stroke();
        context.closePath();
        context.restore();
        context.translate(-centerX,-centerY);
}


	function throttle(value)
	{
		// var value = $('#throttle_value').val();
		  
		var output = "";
		value = parseInt(value);
		if (value < 0)
		{
			output = -1 * value + "% reverse";
			draw(-1 * value);
			value -= 40;

		}
		else if (value > 0)
		{
			output = value + "% forward";
			draw(value);
			value = value + 40;
		}
		else
		{
			value = 0
			output = value + "% forward"
			draw(value);
			document.getElementById("throttle_value").value = 0;
		}
		document.querySelector('#throttle_output').value = output;

		$.post( "/throttle?v=" + value, function(data) {
		  if (data = "SUCCESS")
		  {
				
		  	//console.log("SUCCESS");
		  }
		  else
		  {
		  	console.log("FAILURE");
		  }
		});

	}

	function steering(value)
	{
	  var value = 0;
	  if ($("#turn_left").is(':checked'))
  	{
  		console.log("left");
  		value = -100;
  	}
  	else if ($("#turn_forward").is(':checked'))
  	{
  		console.log("center");
  		value = 0;

  	}
  	else if ($("#turn_right").is(':checked'))
  	{
  		console.log("right");
  		value = 100;

  	}

			
		$.post( "/steering?v=" + value, function(data) {
		  if (data = "SUCCESS")
		  {
		  	console.log("SUCCESS");
		  }
		  else
		  {
		  	console.log("FAILURE");
		  }
		});

	}

	function acc()
	{
		if (enable_acc)
		{
			console.log("disabled");
			enable_acc = false;
		}
		else
		{
			console.log("enabled");
			enable_acc = true;
		}
	}
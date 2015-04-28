/*
Configuration note:: trottle / steering status files will be created in function 
that tell variableSpeed function stop singling motor movement.

Purdue University
CNIT 315
Team Hot Wheels
Members::
Tim Cahoe
Matt Depue
Matt Morehouse
Nathan Morin @nathanamorin

*/
#include "hotWheelsLib.h"
#include <pthread.h>
#include <stdio.h>
#include <string.h>

int initialized = FALSE;
int frequency = 1/50;

char throttleFile[9] = "throttle";
char steeringFile[9] = "steering";

int initHotWheels()
{
	wiringPiSetup();
	//Set up pins
	pinMode(GPIO_RIGHT, OUTPUT);
	pinMode(GPIO_LEFT, OUTPUT);
	pinMode(GPIO_FORWARD, OUTPUT);
	pinMode(GPIO_BACK, OUTPUT);

	//Set initial low values;
	clearThrottle();
	clearSteering();

	initialized = TRUE;
	return SUCCESS;
}

int variableSpeed(struct varSpeedInput data)
{
	if (!initialized) return FAILURE;
	int GPIO = data.GPIO;
	char *fileLoc;
	strcpy(fileLoc, data.fileLoc);
	
	FILE *file;
	int wait_time_on = 1000 * frequency * ((varSpeedInput.value)/100);
	int wait_time_off = 1000 * frequency * ((100-varSpeedInput.value)/100);
	for(;;)
	{
		file = fopen(fileLoc, "r");
		if (fgetc(file) == STOP_CAR) return SUCCESS;
		fclose(file);

		digitalWrite(GPIO, HIGH);
		delay(wait_time_on);
		
		digitalWrite(GPIO, LOW);
		delay(wait_time_off);

	}


	return SUCCESS;
}



int throttle(int value)
{
  if (!initialized) return;
  pthread_t thread;
  
  if (value < 0)
  {
    value = -value;
    struct varSpeedInput data = {value,GPIO_BACK,throttleFile};
    pthread_create(&thread,NULL, variableSpeed, data);

  }
  
  else if (value > 0)
  {
    struct varSpeedInput data = {value,GPIO_FORWARD,throttleFile};
    pthread_create(&thread,NULL, variableSpeed, data);
	}

	else if (value == 0)
  {
    printf("Please select a value for the speed.");
  }

  return SUCCESS;
}



int steering(int value)
{
  if (!initialized) return;
  pthread_t thread;
  
  if (value < 0)
  {
    value = -value;
    struct varSpeedInput data = {value,GPIO_LEFT,steeringFile};
    pthread_create(&thread,NULL, variableSpeed, data);

  }
  
  else if (value > 0)
  {
    struct varSpeedInput data = {value,GPIO_RIGHT,steeringFile};
    pthread_create(&thread,NULL, variableSpeed, data);
	}

	else if (value == 0)
  {
    printf("Please select a value for the speed.");
  }

  return SUCCESS;
}



int clearThrottle()
{
	if (!initialized) return FAILURE;

	file = fopen(throttleFile, "w");
	fputc(STOP_CAR,file);
	fclose(file);

	return SUCCESS;
}



int clearSteering()
{
	if (!initialized) return FAILURE;
	file = fopen(steeringFile, "w");
	fputc(STOP_CAR,file);
	fclose(file);

	return SUCCESS;
}


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
double frequency = 1.0/400.0;

int throttleVal = 0;
int steeringVal = 0;

struct varSpeedInput throttleData;
struct varSpeedInput steeringData;

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

void *variableSpeed(void *input)
{
	
	if (!initialized) return;

	struct varSpeedInput *data = input;
	int GPIO = data->GPIO;
	printf("GPIO %d\n",GPIO );
	FILE *file;
	int wait_time_on = 1000 * frequency * (((double)data->value)/100.0);
	int wait_time_off = 1000 * frequency * ((100.0-(double)data->value)/100.0);
	for(;;)
	{
		if (*(data->enabled) == FALSE)
		{
			break;
		}
		//printf("%d\n", GPIO_FORWARD);
		digitalWrite(GPIO, HIGH);
		delay(wait_time_on);

		digitalWrite(GPIO, LOW);
		delay(wait_time_off);

	}



	return;
}



int throttle(int value)
{
  if (!initialized) return FAILURE;
  clearThrottle();
  throttleVal = TRUE;
  pthread_t thread;
  
  if (value < 0)
  {
    value = -value;
    throttleData.value = value;
    throttleData.GPIO = GPIO_BACK;
    throttleData.enabled = &throttleVal;
    // strcpy(data.fileLoc,throttleFile);
    pthread_create(&thread,NULL, variableSpeed, &throttleData);

  }
  
  else if (value > 0)
  {
    throttleData.value = value;
    throttleData.GPIO = GPIO_FORWARD;
    throttleData.enabled = &throttleVal;
    //printf("GPIO Data %d\n", data.GPIO);
    // strcpy(data.fileLoc,throttleFile);
    pthread_create(&thread,NULL, variableSpeed, &throttleData);
	}

	else if (value == 0)
  {
    printf("Please select a value for the speed.");
  }

  return SUCCESS;
}



int steering(int value)
{
  if (!initialized) return FAILURE;
  clearSteering();
  // steeringVal = TRUE;
  // pthread_t thread;
  // printf("Steering func %d\n", value);
  
  if (value < 0)
  {
    // steeringData.value = value;
    // steeringData.GPIO = GPIO_LEFT;
    // steeringData.enabled = &steeringVal;
    // pthread_create(&thread,NULL, variableSpeed, &steeringData);
    digitalWrite(GPIO_LEFT, HIGH);


  }
  
  else if (value > 0)
  {
    // steeringData.value = value;
    // steeringData.GPIO = GPIO_RIGHT;
    // steeringData.enabled = &steeringVal;
    // pthread_create(&thread,NULL, variableSpeed, &steeringData);
    digitalWrite(GPIO_RIGHT, HIGH);
	}

  return SUCCESS;
}



int clearThrottle()
{
	//if (!initialized) return FAILURE;

	// FILE *file = fopen(throttleFile, "w");
	// fputc(STOP_CAR,file);
	// fclose(file);
	throttleVal = FALSE;
	delay(21);
	digitalWrite(GPIO_FORWARD, LOW);
	digitalWrite(GPIO_BACK, LOW);
	return SUCCESS;
}



int clearSteering()
{
	if (!initialized) return FAILURE;
	// FILE *file = fopen(steeringFile, "w");
	// fputc(STOP_CAR,file);
	// fclose(file);
	// steeringVal = FALSE;
	//delay(110);
	digitalWrite(GPIO_RIGHT, LOW);
	digitalWrite(GPIO_LEFT, LOW);


	return SUCCESS;
}


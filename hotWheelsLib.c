/*
Configuration note:: trottle / steering status files will be created in function 
that tell variableSpeed function stop singling motor movement.

Purdue University
CNIT 315
Team Hot Wheels
Members::
Tim Cahoe
Matt Depue
Matt Morehosue
Nathan Morin @nathanamorin

*/
#include "hotWheelsLib.h"

int initialized = FALSE;
int frequency = 1/50;

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

int variableSpeed(int value, int GPIO, char *fileLoc)
{
	if (!initialized) return FAILURE;
	
	FILE *file;
	int wait_time_on = 1000 * frequency * ((value)/100);
	int wait_time_off = 1000 * frequency * ((100-value)/100);
	for(;;)
	{
		file = fopen(fileLc, "r");
		if (fgetc(file) == STOP_CAR) return SUCCESS;

		digitalWrite(GPIO, HIGH);
		delay(wait_time_on);
		
		digitalWrite(GPIO, LOW);
		delay(wait_time_off);

	}


	return SUCCESS;
}



int throttle(int value)
{
	if (!initialized) return FAILURE;


	return SUCCESS;
}



int steering(int value)
{
	if (!initialized) return FAILURE;


	return SUCCESS;
}



int clearThrottle()
{
	if (!initialized) return FAILURE;


	return SUCCESS;
}



int clearSteering()
{
	if (!initialized) return FAILURE;


	return SUCCESS;
}


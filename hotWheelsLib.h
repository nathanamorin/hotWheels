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
#include <stdlib.h>
#include <stdio.h>
#include <wiringPi.h>

#ifndef SUCCESS
#define SUCCESS 1
#endif

#ifndef FAILURE
#define FAILURE 0
#endif

#ifndef TRUE
#define TRUE 1
#endif

#ifndef FALSE
#define FALSE 0
#endif

#ifndef STOP_CAR
#define STOP_CAR 's'
#endif

#ifndef GPIO_RIGHT
#define GPIO_RIGHT 0
#endif

#ifndef GPIO_LEFT
#define GPIO_LEFT 2
#endif

#ifndef GPIO_BACK
#define GPIO_BACK 8
#endif

#ifndef GPIO_FORWARD
#define GPIO_FORWARD 7
#endif


struct varSpeedInput
{
	int value;
	int GPIO;
	char fileLoc[50];
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//BASE FUNCTIONS

int initHotWheels()

/*
Value is a number between 0 - 100, 0 off, 100 full.
PWM Theory - http://raspi.tv/2013/rpi-gpio-0-5-2a-now-has-software-pwm-how-to-use-it
Status file somewhere in filesystem that tells when to stop.
*/
int variableSpeed(struct varSpeedInput data);
/*
Value is number between -100 and + 100 where -100 is full reverse and + 100 is full forward
DEPENDS on variableSpeed*
*/
int throttle(int value);
/*
Value is number between -100 and + 100 where -100 is full turn left and + 100 is full turn right
DEPENDS on variableSpeed*
*/
int steering(int value);
/*
Sets the trottle speed to 0 while updating trottle status file
*/
int clearThrottle();
/*
Sets the steering speed to 0 while updating steering status file
*/
int clearSteering();



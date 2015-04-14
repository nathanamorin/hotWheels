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


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//BASE FUNCTIONS

/*
Value is a number between 0 - 100, 0 off, 100 full.

Status file somewhere in filesystem that tells when to stop.
*/
int variableSpeed(int value);
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



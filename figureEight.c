/*
Suggested function for automatic figure 8, not tested

Purdue University
CNIT 315
Team Hot Wheels
Members::
Tim Cahoe
Matt Depue
Matt Morehouse
Nathan Morin @nathanamorin

*/

int figureEight(int value)
{

int delayTime = value/100;

throttle(100);
delay(delayTime);
steering(1);
delay(delayTime);
clearSteering();
delay(delayTime);
steering(-1);
delay(delayTime);
clearSteering();
delay(delayTime);
throttle(0);

return 0;
}

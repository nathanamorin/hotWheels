

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

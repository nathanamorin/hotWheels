#!/bin/sh
sleep 1
sudo /home/pi/hotWheels/hostapd/hostapd /home/pi/hotWheels/hostapd/hostapd.conf &
sleep 10
sudo /home/pi/hotWheels/webServer/hotWheelsServer

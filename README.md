# Team Hot Wheels
Matthew Morehouse, Tim Cahoe, Nathan Morin, Matthew Depue

Purdue University CNIT 315
Professor Eric Matson

## Introduction

This project will design a C library for controlling a simple off-the-shelf RC car from a on board control unit with local internet access (i.e. raspberry Pi, Arduino).  This library will be demonstrated with a simple web based app that allows the RC car to be navigated through a preset obstacle course.  Below, this team has included the technical requirements for this project, a more detailed project description, next steps for this project, a list of physical components with links to potential products, and references to some preliminary research performed by this team.

## Requirements
* Wiring Pi http://wiringpi.com/ (Version Used Archived under <root>/etc/wiringPi)

## Usage Notes
* Compile hot wheels server with 
```gcc -o hotWheelsServer mongoose.c hotWheelsLib.c hotWheelsServer.c -lpthreads -lwiringPi```
* Run hot Wheels server with root privilages to run on web port 80.  NOTE: web socket can be configured in hotWheelsServer.c

## Documentation

### GPIO PINS USED on Raspberry Pi B+ 
(note, these values be changed in hotWheelsLib.h)
* GPIO 0 - turn right
* GPIO 2 - turn left
* GPIO 8 - go back
* GPIO 7 - go forward

### Sample Components List
* RC car - http://www.amazon.com/gp/product/B004CPARWK/ref=oh_aui_detailpage_o00_s00
* Raspberry Pi - http://www.amazon.com/gp/product/B00AJGM37I/ref=oh_aui_detailpage_o00_s00
* Breadboard - http://www.amazon.com/microtivity-IB401-400-point-Experiment-Breadboard/dp/B004RXKWDQ/ref=sr_1_1
* Motor Controller Interface Unit - http://www.amazon.com/gp/product/B00AJGM37I/ref=oh_aui_detailpage_o00_s00
* Battery Pack - http://www.amazon.com/PNY-Universal-Portable-Rechargeable-Battery/dp/B00LNB2VZW/ref=sr_1_2
* USB Wifi Card - http://www.amazon.com/Wi-Pi-Raspberry-802-11n-Wireless-Adapter/dp/B00BDW6D7I


## References

* Web Server
  - https://github.com/cesanta/mongoose

* Raspberry Pi GPIO
  - http://pi4j.com/pins/model-b-plus.html
  - http://wiringpi.com/the-gpio-utility/

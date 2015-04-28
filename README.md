# Team Hot Wheels
Matthew Morehouse, Tim Cahoe, Nathan Morin, Matthew Depue

Purdue University CNIT 315
Professor Eric Matson

## Introduction

This project will design a C library for controlling a simple off-the-shelf RC car from a on board control unit with local internet access (i.e. raspberry Pi, Arduino).  This library will be demonstrated with a simple web based app that allows the RC car to be navigated through a preset obstacle course.  Below, this team has included the technical requirements for this project, a more detailed project description, next steps for this project, a list of physical components with links to potential products, and references to some preliminary research performed by this team.

## Requirements
* Wiring Pi http://wiringpi.com/ (Version Used Archived under <root>/wiringPi)

## Documentation
* GPIO 0 - turn right
* GPIO 2 - turn left
* GPIO 8 - go back
* GPIO 7 - go forward

## References

* Web Server
  - https://www.gnu.org/software/libmicrohttpd/
  - http://grothoff.org/christian/mhd2013gpn.pdf
  - https://gnunet.org/svn/libmicrohttpd/src/examples/fileserver_example.c
  - http://sourcecodebrowser.com/libmicrohttpd/0.2.0/fileserver__example_8c_source.html

* Raspberry Pi GPIO
  - http://pi4j.com/pins/model-b-plus.html
  - http://wiringpi.com/the-gpio-utility/

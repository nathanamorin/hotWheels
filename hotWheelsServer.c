/*
Hot Wheels Web Server
Requires mongoose web server

Purdue University
CNIT 315
Team Hot Wheels
Members::
Tim Cahoe
Matt Depue
Matt Morehouse
Nathan Morin @nathanamorin

*/

#include "mongoose.h"
#include "hotWheelsLib.h"
#include<stdlib.h>
#include<string.h>


int getValue(struct mg_connection *conn)
{
  char inputVal[10];
  
  mg_get_var(conn, "v", inputVal, sizeof(inputVal));
  int value = atoi(inputVal);
  
  if (value > 100) value = 100;
  if (value < -100) value = -100;

  return value;
}

static int ev_handler(struct mg_connection *conn, enum mg_event ev) {
  switch (ev) {
    case MG_REQUEST:

      //Static Files : exit to general file handlers
      if (strncmp(conn->uri,"/static",7) == 0)
      {
        return MG_FALSE;
      }

      //Car Controll Page /race
      if (strncmp(conn->uri,"/race",5) == 0)
      {
        mg_send_file(conn, "html/race.html", NULL);
        return MG_MORE;
      }
      
      //API Function : called to move car forward / backward
      if (strncmp(conn->uri,"/throttle",9) == 0)
      {
        int value = getValue(conn);
        
        if (value == 0) 
        {
          clearThrottle();
        }
        else
        {
          throttle(value);
        }

        mg_printf_data(conn, "SUCCESS");

        return MG_TRUE;
      }

      //API Function : called to move car left / right
      if (strncmp(conn->uri,"/steering",9) == 0)
      {
        int value = getValue(conn);
        
        if (value == 0) 
        {
          clearSteering();
        }
        else
        {
          steering(value);
        }

        mg_printf_data(conn, "SUCCESS");

        return MG_TRUE;
      }

      //Default page returned if no specific handler is found
      mg_send_file(conn, "html/index.html", NULL);
      return MG_MORE;


    case MG_AUTH: return MG_TRUE;
    default: return MG_FALSE;
  }
}

int main(void) {
  
  //Initialize GPIO
  initHotWheels();
  
  struct mg_server *server = mg_create_server(NULL, ev_handler);
  //Set to location on Device
  mg_set_option(server, "document_root", ".");
  
  mg_set_option(server, "listening_port", "192.168.10.1:80");
  
  //mg_set_option(server, "document_root", "/home/pi/hotWheels/webServer");
  //mg_set_option(server, "listening_port", "192.168.10.1:80");

  printf("Starting on port %s\n", mg_get_option(server, "listening_port"));
  for (;;) mg_poll_server(server, 1000);
  mg_destroy_server(&server);

  return 0;
}

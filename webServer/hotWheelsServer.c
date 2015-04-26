// Copyright (c) 2014 Cesanta Software
// All rights reserved
//
// This example demostrates how to send arbitrary files to the client.

#include "mongoose.h"
//#include "hotWheelsLib.h"
#include<stdlib.h>
#include<string.h>


int getValue(struct mg_connection *conn)
{
  char inputVal[10];
  mg_get_var(conn, "v", inputVal, sizeof(inputVal));
  int value =atoi(inputVal);
  
  if (value > 100) value = 100;
  if (value < -100) value = -100;

  return value;
}

static int ev_handler(struct mg_connection *conn, enum mg_event ev) {
  switch (ev) {
    case MG_REQUEST:
      //printf("%s\n", conn->uri);
      if (strncmp(conn->uri,"/static",7) == 0)
      {
        printf("%s\n", conn->uri);
        return MG_FALSE;
      }

      if (strncmp(conn->uri,"/race",5) == 0)
      {
        mg_send_file(conn, "html/race.html", NULL);
        return MG_MORE;
      }
      
      if (strncmp(conn->uri,"/throttle",9) == 0)
      {
        int value = getValue(conn);
        printf("Value returned - %d\n", value);

        //throttle(value);

        mg_printf_data(conn, "SUCCESS");

        return MG_TRUE;
      }

      if (strncmp(conn->uri,"/steering",9) == 0)
      {
        int value = getValue(conn);
        printf("Value returned - %d\n", value);

        //steering(value);

        mg_printf_data(conn, "SUCCESS");

        return MG_TRUE;
      }

      mg_send_file(conn, "html/index.html", NULL);  // Also could be a dir, or CGI
      return MG_MORE; // It is important to return MG_MORE after mg_send_file!
    







    case MG_AUTH: return MG_TRUE;
    default: return MG_FALSE;
  }
}

int main(void) {
  struct mg_server *server = mg_create_server(NULL, ev_handler);
  //Change for Actual Car
  mg_set_option(server, "document_root", ".");
  
  mg_set_option(server, "listening_port", "127.0.0.1:80");

  printf("Starting on port %s\n", mg_get_option(server, "listening_port"));
  for (;;) mg_poll_server(server, 1000);
  mg_destroy_server(&server);

  return 0;
}

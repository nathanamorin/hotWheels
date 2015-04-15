// Copyright (c) 2014 Cesanta Software
// All rights reserved
//
// This example demostrates how to send arbitrary files to the client.

#include "mongoose.h"

static int ev_handler(struct mg_connection *conn, enum mg_event ev) {
  switch (ev) {
    case MG_REQUEST:
      printf("%s\n", conn->uri);
      if (strncmp(conn->uri,"/static",7) == 0)
      {
        return MG_FALSE;
      }

      if (strncmp(conn->uri,"/race") == 0)
      {
        mg_send_file(conn, "html/race.html", NULL);
        return MG_MORE;
      }

      mg_send_file(conn, "html/index.html", NULL);  // Also could be a dir, or CGI
      return MG_MORE; // It is important to return MG_MORE after mg_send_file!
    







    case MG_AUTH: return MG_TRUE;
    default: return MG_FALSE;
  }
}

int main(void) {
  struct mg_server *server = mg_create_server(NULL, ev_handler);

  mg_set_option(server, "document_root", "/home/pi/hotWheels/webServer");
  mg_set_option(server, "listening_port", "192.168.10.1:80");

  printf("Starting on port %s\n", mg_get_option(server, "listening_port"));
  for (;;) mg_poll_server(server, 1000);
  mg_destroy_server(&server);

  return 0;
}

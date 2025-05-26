#ifndef ROUTER_H
#define ROUTER_H

#include "../lib/mongoose/mongoose.h"

void routeRequest(struct mg_connection *conn,
                  int event,
                  void *eventData);

#endif
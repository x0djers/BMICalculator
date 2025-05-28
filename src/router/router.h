#ifndef ROUTER_H
#define ROUTER_H

#include <mongoose.h>

void routeRequest(struct mg_connection *connection,
                  int event,
                  void *eventData);

#endif
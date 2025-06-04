#ifndef ROUTER_H
#define ROUTER_H

#include <mongoose.h>

#include <errors/errors.h>

typedef ErrorCode (*routeHandler)(struct mg_connection*, struct mg_http_message*);

struct Route {
    const char* uriPattern;
    const char* httpMethod;
    routeHandler handler;
};

void routeRequest(struct mg_connection *connection,
                  int event,
                  void *eventData);

#endif
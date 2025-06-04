#ifndef SERVER_H
#define SERVER_H

#include <errors/errors.h>

struct mg_connection;

typedef void (*Router)(struct mg_connection *, int, void *);

typedef struct {
    const char* host;
    int port;
    char fullUrl[512];
} ServerAddress;

typedef struct {
    struct mg_mgr* mgr;
    ServerAddress addr;
    Router router;
} Server;

ErrorCode createServer(Server* server, ServerAddress address);

ErrorCode runServer(Server* server);

ErrorCode stopServer(Server* server);

#endif
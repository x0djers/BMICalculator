#ifndef TYPES_H
#define TYPES_H

#include "../lib/mongoose/mongoose.h"

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

#endif

#ifndef SERVER_H
#define SERVER_H

#include <constants/types.h>
#include <constants/errors/errors.h>

ErrorCode createServer(Server* server, ServerAddress address);

ErrorCode runServer(Server* server);

ErrorCode stopServer(Server* server);

#endif
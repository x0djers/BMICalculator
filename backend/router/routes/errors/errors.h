#ifndef ROUTER_ERRORS_H
#define ROUTER_ERRORS_H

#include <mongoose.h>

#include <errors/errors.h>

void sendErrorMessage(struct mg_connection* connection,
                      ErrorCode errorCode);

#endif


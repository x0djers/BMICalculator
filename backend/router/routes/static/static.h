#ifndef STATIC_H
#define STATIC_H

#include <mongoose.h>

#include <constants/errors/errors.h>

ErrorCode handleStatic(struct mg_connection* connection,
                       struct mg_http_message* httpMessage);

#endif

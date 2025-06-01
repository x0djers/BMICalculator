#ifndef API_H
#define API_H

#include <mongoose.h>

#include <errors/errors.h>

ErrorCode handleBmiApi(struct mg_connection* connection,
                       const struct mg_http_message* httpMessage);

#endif

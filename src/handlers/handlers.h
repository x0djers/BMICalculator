#ifndef HANDLERS_H
#define HANDLERS_H

#include <constants/errors/errors.h>

ErrorCode handlePage(struct mg_connection* connection,
                     struct mg_http_message* httpMessage,
                     const char* pagePath);

ErrorCode handleStatic(struct mg_connection* connection,
                       struct mg_http_message* httpMessage);

ErrorCode handleBmiApi(struct mg_connection* connection,
                       const struct mg_http_message* httpMessage);
#endif

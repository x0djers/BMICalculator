#ifndef PAGES_H
#define PAGES_H

#include <mongoose.h>

#include <errors/errors.h>

ErrorCode handlePage(struct mg_connection* connection,
                     struct mg_http_message* httpMessage,
                     const char* pagePath);

#endif
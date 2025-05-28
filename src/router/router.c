#include <string.h>
#include <stdlib.h>

#include <log.h>
#include <mongoose.h>

#include "router.h"
#include <handlers/handlers.h>
#include <constants/constants.h>

void routeRequest(struct mg_connection *connection, const int event, void *eventData) {
    if (event == MG_EV_HTTP_MSG) {
        struct mg_http_message *httpMessage = eventData;
        const struct mg_str uri = httpMessage->uri;

        log_info("Request: %.*s", (int)uri.len, uri.buf);

        if (mg_match(uri, mg_str("/"), NULL) ||
            mg_match(uri, mg_str("/input"), NULL)) {
            handlePage(connection, httpMessage, PATH_INPUT_HTML);

        } else if (mg_match(uri, mg_str("/result"), NULL)) {
            handlePage(connection, httpMessage, PATH_RESULT_HTML);

        } else if (mg_match(uri, mg_str("/api/bmi"), NULL) &&
                   mg_match(httpMessage->method, mg_str("POST"), NULL)) {
            handleBmiApi(connection, httpMessage);

        } else if (mg_match(uri, mg_str("/css/*"), NULL) ||
                   mg_match(uri, mg_str("/js/*"), NULL)) {
            handleStatic(connection, httpMessage);

        } else {
            log_error("404 Not Found: %.*s", (int)uri.len, uri.buf);
            mg_http_reply(connection,
                          404,
                          "Content-Type: %s\r\n",
                          MIME_PLAIN,
                          "404 Not Found\n");
        }
    }
}
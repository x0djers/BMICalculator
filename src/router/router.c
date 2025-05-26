#include <string.h>
#include <stdlib.h>

#include "router.h"
#include "../lib/logger/log.h"
#include "../constants/constants.h"
#include "../lib/mongoose/mongoose.h"

static void sendFile(struct mg_connection *conn,
                      struct mg_http_message *httpMessage,
                      const char *path,
                      const char *mimeType) {
    const struct mg_http_serve_opts opts = {.root_dir = "."};
    log_info("Served file: %s [%s]", path, mimeType);
    mg_http_serve_file(conn, httpMessage, path, &opts);
}

void routeRequest(struct mg_connection *conn, const int event, void *eventData) {
    if (event == MG_EV_HTTP_MSG) {
        struct mg_http_message *httpMessage = eventData;
        const struct mg_str uri = httpMessage->uri;

        log_info("Request: %.*s", (int)uri.len, uri.buf);

        if (mg_match(uri, mg_str("/"), NULL) ||
            mg_match(uri, mg_str("/input"), NULL)) {
            sendFile(conn, httpMessage, PATH_INPUT_HTML, MIME_HTML);

        } else if (mg_match(uri, mg_str("/result"), NULL)) {
            sendFile(conn, httpMessage, PATH_RESULT_HTML, MIME_HTML);

        } else if (mg_match(uri, mg_str("/css/*"), NULL) ||
                   mg_match(uri, mg_str("/js/*"), NULL)) {
            const struct mg_http_serve_opts opts = {
                .root_dir = STATIC_DIR,
            };
            mg_http_serve_dir(conn, httpMessage, &opts);

        } else {
            log_error("404 Not Found: %.*s", (int)uri.len, uri.buf);
            mg_http_reply(conn,
                404,
                   "Content-Type: %s\r\n",
                   MIME_PLAIN,
                          "404 Not Found\n");
        }
    }
}
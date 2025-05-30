#include <sys/stat.h>

#include <log.h>
#include <mongoose.h>

#include <handlers/handlers.h>

ErrorCode handlePage(struct mg_connection* connection,
                       struct mg_http_message* httpMessage,
                       const char* pagePath) {
    ErrorCode errorCode = NONE_ERROR;
    struct stat st;


    log_info("Handling request for page with URI: %.*s",
             (int)httpMessage->uri.len, httpMessage->uri.buf);
    log_info("Resolved page path: %s", pagePath);

    if (stat(pagePath, &st) == 0 && S_ISREG(st.st_mode)) {
        const struct mg_http_serve_opts opts = {.root_dir = "."};
        log_info("Served page by path: %s", pagePath);
        mg_http_serve_file(connection, httpMessage, pagePath, &opts);
    } else {
        errorCode = PAGE_NOT_FOUND_ERROR;
        log_error("%s (%s)", errorsMessages[errorCode], pagePath);
        mg_http_reply(connection,
                      404,
                      "Content-Type: text/plain\r\n",
                      "404 Not Found\n");
    }

    return errorCode;
}
#include <sys/stat.h>

#include <log.h>
#include <mongoose.h>

#include "pages.h"
#include <constants/constants.h>
#include <router/routes/error/error.h>

void getRequiredPagePath(const char* baseDir,
                     const struct mg_str uri,
                     char* outputPath,
                     const size_t outputPathLen) {
    if (uri.len == 1 && uri.buf[0] == '/') {
        snprintf(outputPath, outputPathLen, HONE_DIR);
    } else {
        snprintf(outputPath,
                 outputPathLen,
                 "%s%.*s.html",
                 baseDir,
                 (int)uri.len,
                 uri.buf);
    }
}

ErrorCode handlePage(struct mg_connection* connection,
                     struct mg_http_message* httpMessage) {
    ErrorCode errorCode = NONE_ERROR;
    struct stat st;
    char pagePath[256];

    getRequiredPagePath(PAGES_DIR,
                        httpMessage->uri,
                        pagePath,
                        sizeof(pagePath));

    log_trace("Handling request for page with URI: %.*s",
             (int)httpMessage->uri.len, httpMessage->uri.buf);
    log_trace("Resolved page path: %s", pagePath);

    if (stat(pagePath, &st) == 0 && S_ISREG(st.st_mode)) {
        const struct mg_http_serve_opts opts = {.root_dir = "."};
        log_trace("Served page by path: %s", pagePath);
        mg_http_serve_file(connection, httpMessage, pagePath, &opts);
    } else {
        errorCode = PAGE_NOT_FOUND_ERROR;
        log_error("%s (%s)", errorsMessages[errorCode], pagePath);
        sendErrorMessage(connection, errorCode);
    }

    return errorCode;
}
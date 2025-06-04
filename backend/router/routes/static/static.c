#include <sys/stat.h>

#include <log.h>
#include <mongoose.h>

#include "static.h"
#include <config/config.h>
#include <router/routes/error/error.h>

void getRequiredPath(const char* baseDir,
                     const struct mg_str uri,
                     char* outputPath,
                     const size_t outputPathLen) {
    snprintf(outputPath, outputPathLen, "%s%.*s",
             baseDir, (int)uri.len, uri.buf);
}

bool isValidStaticFile(const char* filePath) {
    struct stat st;
    return stat(filePath, &st) == 0 && S_ISREG(st.st_mode);
}

ErrorCode handleStatic(struct mg_connection* connection,
                              struct mg_http_message* httpMessage) {
    ErrorCode errorCode = NONE_ERROR;

    log_trace("Handling request for URI: %.*s",
             (int)httpMessage->uri.len, httpMessage->uri.buf);

    char requiredPath[PATH_MAX];

    getRequiredPath(globalConfig.staticDir,
                    httpMessage->uri,
                    requiredPath,
                    PATH_MAX);

    log_trace("Resolved static file path: %s", requiredPath);

    if (isValidStaticFile(requiredPath)) {
        log_trace("Static file found: %s", requiredPath);
        const struct mg_http_serve_opts opts = {
            .root_dir = globalConfig.staticDir,
        };
        mg_http_serve_file(connection, httpMessage, requiredPath, &opts);
    } else {
        errorCode = FILE_NOT_FOUND_ERROR;
        log_error("%s (%s)", errorsMessages[errorCode], requiredPath);
        sendErrorMessage(connection, errorCode);

    }

    return errorCode;
}
#include <stdlib.h>

#include <log.h>
#include <mongoose.h>

#include "server.h"

#include <config/config.h>
#include <router/router.h>

void getServerAddress(ServerAddress *addr) {
    snprintf(addr->fullUrl,
             sizeof(addr->fullUrl),
             "%s://%s:%d",
             globalConfig.protocol,
             addr->host,
             addr->port);
}

ErrorCode createServer(Server* server, ServerAddress address) {
    ErrorCode errorCode = NONE_ERROR;

    server->mgr = malloc(sizeof(struct mg_mgr));

    errorCode = !server->mgr ? SERVER_CREAT_FAILED_ERROR : NONE_ERROR;

    if (errorCode == NONE_ERROR) {
        mg_mgr_init(server->mgr);

        getServerAddress(&address);

        server->addr = address;
        server->router = routeRequest;
    }

    if (errorCode == NONE_ERROR) {
        log_trace("Server created successfully");
    } else {
        log_error("Creation server failed with error %d", errorCode);
    }

    return errorCode;
}

ErrorCode runServer(Server* server) {
    ErrorCode errorCode = NONE_ERROR;

    if (!server || !server->mgr) {
        log_error("Invalid server configuration.");
        errorCode = INVALID_SERVER_CONFIG_ERROR;
    } else {
        struct mg_connection *conn = mg_http_listen(server->mgr,
                                                    server->addr.fullUrl,
                                                    server->router,
                                                    server);

        if (!conn) {
            errorCode = SERVER_INIT_FAILED_ERROR;
            log_error("Failed to start server: %d", errorCode);
        } else {
            log_info("Server started successfully at %s", server->addr.fullUrl);
            for (;;)
                mg_mgr_poll(server->mgr, 1000);
        }
    }

    return errorCode;
}

ErrorCode stopServer(Server* server) {
    log_info("Server stopped.");
    if (server->mgr) {
        mg_mgr_free(server->mgr);
        server->mgr = NULL;
    }
    if (server->router) {
        server->router = NULL;
    }
    return NONE_ERROR;
}

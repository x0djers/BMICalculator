#include <log.h>

#include <config/config.h>
#include <server/server.h>

int main() {
    ErrorCode errorCode = loadConfig();

    if (errorCode == NONE_ERROR) {
        log_set_level(globalConfig.logLevel);

        Server server;

        static ServerAddress localHost;
        localHost.host = globalConfig.host;
        localHost.port = globalConfig.port;

        errorCode = createServer(&server, localHost);
        if (errorCode == NONE_ERROR) {
            runServer(&server);
            stopServer(&server);
        }
    }
}
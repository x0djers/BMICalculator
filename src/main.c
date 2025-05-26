#include "server/server.h"
#include "lib/logger/log.h"

int main() {
    log_set_level(LOG_INFO);

    Server server;

    static ServerAddress localHost = {.host="127.0.0.1", .port=8800};

    createServer(&server, localHost);
    runServer(&server);
    stopServer(&server);

    return 0;
}
#include <string.h>
#include <stdlib.h>

#include <log.h>
#include <mongoose.h>

#include "router.h"
#include "routes/api/api.h"
#include "routes/pages/pages.h"
#include "routes/static/static.h"
#include <constants/constants.h>

#include "routes/error/error.h"

static const struct Route routes[] = {
    {HOME_PAGE_PATTERN, "GET", handlePage},
    {INPUT_PAGE_PATTERN, "GET", handlePage},

    {RESULT_PAGE_PATTERN, "GET", handlePage},

    {BMI_API_PAGE_PATTERN, "POST", handleBmiApi},

    {STYLES_PATTERN, "GET", handleStatic},
    {JS_PATTERN, "GET", handleStatic},

    {NULL, NULL, NULL }
};

void routeRequest(struct mg_connection *connection, const int event, void *eventData) {
    if (event == MG_EV_HTTP_MSG) {
        bool isRouteFound = false;
        struct mg_http_message *httpMessage = eventData;
        const struct mg_str uri = httpMessage->uri;
        const struct mg_str method = httpMessage->method;

        log_trace("Request: %.*s  Method: %.*s",
                  (int)uri.len, uri.buf,
                  (int)method.len, method.buf);

        for (const struct Route* route = routes;
             route->uriPattern != NULL && !isRouteFound; route++) {
            if (mg_match(uri, mg_str(route->uriPattern), NULL)) {
                if (route->httpMethod &&
                    mg_match(method, mg_str(route->httpMethod), NULL)) {
                        isRouteFound = true;
                } else if (!route->httpMethod) {
                    isRouteFound = true;
                }

                if (isRouteFound) {
                    route->handler(connection, httpMessage);
                }
            }
        }

        if (!isRouteFound) {
            log_warn("No route for the path was found:  %.*s",
                     (int)uri.len, uri.buf);
            handleErrorPage(connection, PAGE_NOT_FOUND_ERROR);
        }
    }
}

#include <string.h>
#include <stdlib.h>

#include "router.h"
#include "../lib/logger/log.h"
#include "../constants/constants.h"
#include "../lib/mongoose/mongoose.h"
#include "../lib/json/json.h"
#include "../services/bmi/bmi.h"

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

        } else if (mg_match(uri, mg_str("/api/bmi"), NULL) &&
                   mg_match(httpMessage->method, mg_str("POST"), NULL)) {
            char *body_str = strndup(httpMessage->body.buf, httpMessage->body.len);
            if (body_str == NULL) {
                mg_http_reply(conn,
                              500,
                              "",
                              "Internal Server Error");
                return;
            }

            cJSON *json = cJSON_Parse(body_str);
            free(body_str);

            if (json == NULL) {
                mg_http_reply(conn,
                    400,
                      "Content-Type: application/json\r\n",
                      "{\"error\":\"Invalid JSON\"}");
                return;
            }

            const cJSON *weight_json = cJSON_GetObjectItem(json, "weight");
            const cJSON *height_json = cJSON_GetObjectItem(json, "height");
            const cJSON *units_json = cJSON_GetObjectItem(json, "units");

            if (!cJSON_IsNumber(weight_json) || !cJSON_IsNumber(height_json) || !cJSON_IsString(units_json)) {
                cJSON_Delete(json);
                mg_http_reply(conn, 400, "Content-Type: application/json\r\n", "{\"error\":\"Invalid parameters\"}");
                return;
            }

            const float weight = weight_json->valuedouble;
            const float height = height_json->valuedouble;
            const char *units = units_json->valuestring;

            const float bmi = calculateBMI(height, weight, units);

            char response[100];
            snprintf(response, sizeof(response), "{\"bmi\": %.2f}", bmi);

            cJSON_Delete(json);

            mg_http_reply(conn, 200,
                          "Content-Type: application/json\r\n",
                          "%s", response);

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
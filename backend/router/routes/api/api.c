#include <log.h>
#include <json.h>
#include <mongoose.h>

#include "api.h"
#include <services/bmi/bmi.h>
#include <router/routes/error/error.h>

ErrorCode parseApiParameters(const char* bodyStr,
                             float* parsedWeight,
                             float* parsedHeight,
                             char** parsedUnits) {
    ErrorCode errorCode = NONE_ERROR;

    cJSON* json = cJSON_Parse(bodyStr);

    if (json == NULL) {
        errorCode = INVALID_API_REQUEST_ERROR;
    } else {
        const cJSON *weight_json = cJSON_GetObjectItem(json, "weight");
        const cJSON *height_json = cJSON_GetObjectItem(json, "height");
        const cJSON *units_json = cJSON_GetObjectItem(json, "units");

        if (!cJSON_IsNumber(weight_json) ||
            !cJSON_IsNumber(height_json) ||
            !cJSON_IsString(units_json)) {
            errorCode = INVALID_API_PARAMETERS_ERROR;
        } else {
            *parsedWeight = weight_json->valuedouble;
            *parsedHeight = height_json->valuedouble;
            *parsedUnits = strdup(units_json->valuestring);
        }
    }

    cJSON_Delete(json);

    return errorCode;
}


ErrorCode handleBmiApi(struct mg_connection* connection,
                       struct mg_http_message* httpMessage) {
    ErrorCode errorCode = NONE_ERROR;

    float weight = 0, height = 0;
    char* units = NULL;

    log_info("Started BMI API request processing");

    char* body_str = strndup(httpMessage->body.buf, httpMessage->body.len);
    if (body_str == NULL) {
        errorCode = MEMORY_ALLOCATION_ERROR;
        log_error("%s", errorCode);
        sendErrorMessage(connection, errorCode);
    } else {
        errorCode = parseApiParameters(body_str, &weight, &height, &units);

        log_trace("Parsed parameters: weight=%.2f, height=%.2f, units=%s",
                  weight, height, units);

        if (errorCode == INVALID_API_REQUEST_ERROR ||
            errorCode == INVALID_API_PARAMETERS_ERROR) {
            log_error("%s", errorCode);
            sendErrorMessage(connection, errorCode);
        } else {
            const float bmi = calculateBMI(height, weight, units);

            log_trace("Calculated BMI: %.2f", bmi);

            char response[100];
            snprintf(response, sizeof(response), "{\"bmi\": %.2f}", bmi);

            mg_http_reply(connection,
                          200,
                          "Content-Type: application/json\r\n",
                          "%s", response);

            log_info("Request to the BMI API successfully processed");
        }
    }

    free(body_str);
    free(units);

    return errorCode;
}
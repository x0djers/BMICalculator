#include <stdio.h>
#include <stddef.h>
#include <string.h>

#include <ini.h>
#include <log.h>

#include "config.h"

#define OFFSET(member) offsetof(AppConfig, member)

AppConfig globalConfig;

static const ConfigField configFields[] = {
    {"Server", "host", CONFIG_TYPE_STRING, OFFSET(host)},
    {"Server", "port", CONFIG_TYPE_INT, OFFSET(port)},
    {"Server", "protocol", CONFIG_TYPE_STRING, OFFSET(protocol)},

    {"Paths", "static_dir", CONFIG_TYPE_STRING, OFFSET(staticDir)},
    {"Paths", "pages_dir", CONFIG_TYPE_STRING, OFFSET(pagesDir)},
    {"Paths", "templates_dir", CONFIG_TYPE_STRING, OFFSET(templatesDir)},
    {"Paths", "input_page", CONFIG_TYPE_STRING, OFFSET(inputPage)},
    {"Paths", "result_page", CONFIG_TYPE_STRING, OFFSET(resultPage)},
    {"Paths", "error_page", CONFIG_TYPE_STRING, OFFSET(errorPage)},
    {"Paths", "home_page", CONFIG_TYPE_STRING, OFFSET(homePage)},

    {"Logging", "log_level", CONFIG_TYPE_INT, OFFSET(logLevel)},
};

static const size_t configFieldsCount = sizeof(configFields) /
                                        sizeof(configFields[0]);

static int configHandler(void* user,
                         const char* section,
                         const char* name,
                         const char* value) {
    AppConfig* config = user;
    int handled = 0;

    for (size_t iter = 0; iter < configFieldsCount; iter++) {
        if (strcmp(section, configFields[iter].section) == 0 &&
            strcmp(name, configFields[iter].name) == 0 &&
            !handled) {

            void* fieldPtr = (char*)config + configFields[iter].offset;

            if (configFields[iter].type == CONFIG_TYPE_STRING) {
                strncpy(fieldPtr, value, 255);
                ((char*)fieldPtr)[255] = '\0';
            } else if (configFields[iter].type == CONFIG_TYPE_INT) {
                *(int*)fieldPtr = atoi(value);
            }

            handled = 1;
            }
    }

    if (!handled) {
        log_error("Unknown config parameter: [%s] %s\n", section, name);
    }

    return 1;
}


ErrorCode loadConfig() {
    ErrorCode errorCode = NONE_ERROR;

    memset(&globalConfig, 0, sizeof(globalConfig));
    if (ini_parse(CONFIG_FILE, configHandler, &globalConfig) < 0) {
        log_error("Failed to load config file: %s", CONFIG_FILE);
        errorCode = INVALID_SERVER_CONFIG_ERROR;
    }

    return errorCode;
}

#ifndef CONFIG_H
#define CONFIG_H

#include <stdlib.h>
#include <errors/errors.h>

#define CONFIG_FILE "backend/config/config.ini"

typedef struct {
    char host[64];
    int port;
    char protocol[16];

    char staticDir[256];
    char pagesDir[256];
    char templatesDir[256];
    char inputPage[256];
    char resultPage[256];
    char errorPage[256];
    char homePage[256];

    int logLevel;
} AppConfig;

typedef enum {
    CONFIG_TYPE_STRING,
    CONFIG_TYPE_INT
} ConfigType;

typedef struct {
    const char* section;
    const char* name;
    ConfigType type;
    size_t offset;
} ConfigField;

extern AppConfig globalConfig;

ErrorCode loadConfig();

#endif

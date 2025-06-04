#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "render.h"
#include <errors/errors.h>

ErrorCode readFile(const char* path, char** output) {
    ErrorCode errorCode = NONE_ERROR;

    FILE *file = fopen(path, "r");

    if (file) {
        fseek(file, 0, SEEK_END);
        const size_t size = ftell(file);
        rewind(file);

        *output = malloc(size + 1);
        if (*output) {
            const size_t bytesRead = fread(*output, 1, size, file);
            (*output)[bytesRead] = '\0';
        } else {
            errorCode = MEMORY_ALLOCATION_ERROR;
        }

        fclose(file);
    } else {
        errorCode = FILE_READ_ERROR;
    }

    return errorCode;
}

ErrorCode renderTemplate(const char* templatePath,
                         const char** keys,
                         const char** values,
                         char** renderedTemplate) {
    ErrorCode errorCode = NONE_ERROR;
    char *template = NULL;
    char *result = NULL;

    errorCode = readFile(templatePath, &template);

    if (errorCode == NONE_ERROR && template) {
        size_t resultSize = strlen(template) + 1;
        result = malloc(resultSize);
        if (result) {
            strcpy(result, template);
            free(template);
            template = NULL;

            size_t iter = 0;
            while (keys[iter] != NULL && values[iter] != NULL &&
                   errorCode == NONE_ERROR) {
                char placeholder[256];
                snprintf(placeholder,
                         sizeof(placeholder),
                         "{{%s}}",
                         keys[iter]);

                char* pos = strstr(result, placeholder);
                while (pos != NULL && errorCode == NONE_ERROR) {
                    const size_t beforeLen = pos - result;
                    const size_t placeholderLen = strlen(placeholder);
                    const size_t afterLen = strlen(pos + placeholderLen);
                    const size_t valueLen = strlen(values[iter]);
                    const size_t newLen = beforeLen + valueLen + afterLen + 1;

                    if (newLen > resultSize) {
                        char* newResult = realloc(result, newLen);
                        if (newResult) {
                            result = newResult;
                            resultSize = newLen;
                            pos = result + beforeLen;
                        } else {
                            errorCode = MEMORY_ALLOCATION_ERROR;
                        }
                    }

                    if (errorCode == NONE_ERROR) {
                        memmove(pos + valueLen,
                                pos + placeholderLen,
                                afterLen + 1);
                        memcpy(pos, values[iter], valueLen);
                        pos = strstr(result, placeholder);
                    }
                }

                iter++;
            }

            if (errorCode == NONE_ERROR) {
                *renderedTemplate = result;
                result = NULL;
            }
        } else {
            errorCode = MEMORY_ALLOCATION_ERROR;
        }
    }

    if (result) {
        free(result);
    }
    if (template) {
        free(template);
    }

    return errorCode;
}

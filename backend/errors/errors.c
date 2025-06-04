#include "errors.h"

const int errorsHttpCodes[ERRORS_COUNT] = {
    [NONE_ERROR] = 200,
    [MEMORY_ALLOCATION_ERROR] = 500,
    [SERVER_CREAT_FAILED_ERROR] = 500,
    [SERVER_INIT_FAILED_ERROR] = 500,
    [INVALID_SERVER_CONFIG_ERROR] = 500,
    [PAGE_NOT_FOUND_ERROR] = 404,
    [FILE_NOT_FOUND_ERROR] = 404,
    [FILE_READ_ERROR] = 404,
    [INVALID_API_REQUEST_ERROR]  = 400,
    [INVALID_API_PARAMETERS_ERROR] = 422
};

const char* errorsMessages[ERRORS_COUNT] = {
    [NONE_ERROR] = "No error occurred.",
    [MEMORY_ALLOCATION_ERROR] = "Memory allocation failed.",
    [SERVER_CREAT_FAILED_ERROR] = "Failed to create server",
    [SERVER_INIT_FAILED_ERROR] = "Failed to initialize server.",
    [INVALID_SERVER_CONFIG_ERROR] = "Invalid server configuration.",
    [PAGE_NOT_FOUND_ERROR] = "Requested page not found.",
    [FILE_NOT_FOUND_ERROR] = "Requested file not found.",
    [FILE_READ_ERROR] = "Reading error of the requested file.",
    [INVALID_API_REQUEST_ERROR]  = "Invalid API request format.",
    [INVALID_API_PARAMETERS_ERROR] = "Invalid or missing API parameters."
};

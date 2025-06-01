#include "errors.h"

const char* errorsMessages[ERRORS_COUNT] = {
    [NONE_ERROR] = "No error occurred.",
    [MEMORY_ALLOCATION_ERROR] = "Memory allocation failed.",
    [SERVER_CREAT_FAILED_ERROR] = "Failed to create server",
    [SERVER_INIT_FAILED_ERROR] = "Failed to initialize server.",
    [INVALID_SERVER_CONFIG_ERROR] = "Invalid server configuration.",
    [PAGE_NOT_FOUND_ERROR] = "Requested page not found.",
    [FILE_NOT_FOUND_ERROR] = "Requested file not found.",
    [INVALID_API_REQUEST_ERROR]  = "Invalid API request format.",
    [INVALID_API_PARAMETERS_ERROR] = "Invalid or missing API parameters."
};

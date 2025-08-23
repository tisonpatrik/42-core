#include "../../include/error_utils.h"
#include <stddef.h>

// Error message lookup table
static const char* const error_messages[] = {
    "Success",                           // SUCCESS (0)
    "General failure",                   // FAILURE (1)
    "Null pointer error",                // ERROR_NULL_POINTER (-1)
    "Memory allocation failed",          // ERROR_MEMORY_ALLOCATION (-2)
    "File operation failed",             // ERROR_FILE_OPERATION (-3)
    "Invalid input parameters",          // ERROR_INVALID_INPUT (-4)
    "JSON parsing error",                // ERROR_JSON_PARSING (-5)
    "Stack operation failed"             // ERROR_STACK_OPERATION (-6)
};

const char* get_error_message(int error_code) {
    // Convert negative error codes to positive indices
    unsigned int index;
    
    if (error_code >= 0) {
        index = (unsigned int)error_code;
    } else {
        index = (unsigned int)(-error_code);
    }
    
    // Bounds checking - ensure index is within array bounds
    const size_t array_size = sizeof(error_messages) / sizeof(error_messages[0]);
    if (index < array_size) {
        return error_messages[index];
    }
    
    return "Unknown error code";
}

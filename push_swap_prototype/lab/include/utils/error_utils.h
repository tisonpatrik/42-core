#ifndef ERROR_UTILS_H
# define ERROR_UTILS_H

// Standardized error codes for the entire project
#define SUCCESS 0
#define FAILURE 1

// Specific error codes for different types of failures
#define ERROR_NULL_POINTER -1
#define ERROR_MEMORY_ALLOCATION -2
#define ERROR_FILE_OPERATION -3
#define ERROR_INVALID_INPUT -4
#define ERROR_JSON_PARSING -5
#define ERROR_STACK_OPERATION -6

// Error handling macros for cleaner code
#define RETURN_IF_NULL(ptr) if (!(ptr)) return ERROR_NULL_POINTER
#define RETURN_IF_FAIL(condition) if (condition) return FAILURE
#define RETURN_SUCCESS return SUCCESS
#define RETURN_FAILURE return FAILURE

// Error message helper (for debugging)
const char* get_error_message(int error_code);

// Check if return value indicates success
#define IS_SUCCESS(result) ((result) == SUCCESS)
#define IS_FAILURE(result) ((result) != SUCCESS)

#endif

#ifndef FILE_UTILS_H
# define FILE_UTILS_H

#include "error_utils.h"

// File I/O utilities
int ensure_directory_exists(const char *path);
int save_json_to_file(const char *filepath, const char *json_string);

#endif

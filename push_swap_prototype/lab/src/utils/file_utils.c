#include "../../include/file_utils.h"
#include <stdio.h>
#include <sys/stat.h>

// File I/O utilities
int ensure_directory_exists(const char *path) {
    RETURN_IF_NULL(path);
    
    // Check if directory already exists
    struct stat st;
    if (stat(path, &st) == 0 && S_ISDIR(st.st_mode)) {
        RETURN_SUCCESS; // Directory already exists
    }
    
    // Try to create directory
    if (mkdir(path, 0755) == 0) {
        RETURN_SUCCESS; // Directory created successfully
    }
    
    // If mkdir failed, it might be because parent directories don't exist
    // For now, we'll return failure - in a production system you'd want
    // to implement recursive directory creation
    RETURN_FAILURE;
}

int save_json_to_file(const char *filepath, const char *json_string) {
    RETURN_IF_NULL(filepath);
    RETURN_IF_NULL(json_string);
    
    FILE *file = fopen(filepath, "w");
    if (!file) {
        RETURN_FAILURE;
    }
    
    if (fprintf(file, "%s", json_string) > 0) {
        fclose(file);
        printf("Results saved to: %s\n", filepath);
        RETURN_SUCCESS;
    } else {
        fclose(file);
        printf("Failed to save results to file: %s\n", filepath);
        RETURN_FAILURE;
    }
}

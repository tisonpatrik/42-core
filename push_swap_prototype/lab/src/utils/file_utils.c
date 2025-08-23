#include <stdio.h>
#include <stdlib.h>

// Constants to replace magic numbers
#define MAX_PATH_LENGTH 512
#define MAX_FILEPATH_LENGTH 256

// File I/O utilities
int ensure_directory_exists(const char *path) {
    if (!path) return 0;
    
    char mkdir_cmd[MAX_PATH_LENGTH];
    snprintf(mkdir_cmd, sizeof(mkdir_cmd), "mkdir -p %s", path);
    return system(mkdir_cmd) == 0;
}

int save_json_to_file(const char *filepath, const char *json_string) {
    if (!filepath || !json_string) return 0;
    
    FILE *file = fopen(filepath, "w");
    if (!file) return 0;
    
    int success = fprintf(file, "%s", json_string) > 0;
    fclose(file);
    
    if (success) {
        printf("Results saved to: %s\n", filepath);
    } else {
        printf("Failed to save results to file: %s\n", filepath);
    }
    
    return success;
}

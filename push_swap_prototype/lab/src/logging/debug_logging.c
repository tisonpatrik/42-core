/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_logging.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: patrik <patrik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/24 18:45:00 by patrik            #+#    #+#              */
/*   Updated: 2025/08/24 18:45:00 by patrik           ###   ########.fr        */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/debug_logging.h"
#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

// Global debug configuration
static t_debug_config g_debug_config = {false, false, NULL, DEBUG_INFO};
static FILE *g_log_file = NULL;

// Get current timestamp string
static char *get_timestamp(void) {
    static char timestamp[32];
    time_t now = time(NULL);
    struct tm *tm_info = localtime(&now);
    
    strftime(timestamp, sizeof(timestamp), "%Y-%m-%d %H:%M:%S", tm_info);
    return timestamp;
}

// Initialize debug logging
void debug_init(const char *log_dir, int log_level) {
    if (!log_dir) return;
    
    // Set log level from parameter
    g_debug_config.log_level = log_level;
    
    // Create logs directory if it doesn't exist
    struct stat st = {0};
    if (stat(log_dir, &st) == -1) {
        mkdir(log_dir, 0755);
    }
    
    // Generate log filename with timestamp
    char log_filename[256];
    time_t now = time(NULL);
    struct tm *tm_info = localtime(&now);
    
    snprintf(log_filename, sizeof(log_filename), 
             "%s/push_swap_%04d-%02d-%02d_%02d-%02d-%02d.log",
             log_dir, 
             tm_info->tm_year + 1900, tm_info->tm_mon + 1, tm_info->tm_mday,
             tm_info->tm_hour, tm_info->tm_min, tm_info->tm_sec);
    
    // Open log file
    g_log_file = fopen(log_filename, "w");
    if (g_log_file) {
        g_debug_config.enable_logging = true;
        g_debug_config.log_to_file = true;
        g_debug_config.log_file_path = log_filename;
        
        // Write header
        fprintf(g_log_file, "=== Push Swap Debug Log ===\n");
        fprintf(g_log_file, "Started: %s\n", get_timestamp());
        fprintf(g_log_file, "Log Level: %d\n", g_debug_config.log_level);
        fprintf(g_log_file, "==========================\n\n");
        fflush(g_log_file);
    }
}

// Cleanup debug logging
void debug_cleanup(void) {
    if (g_log_file) {
        fprintf(g_log_file, "\n=== Log Ended: %s ===\n", get_timestamp());
        fclose(g_log_file);
        g_log_file = NULL;
    }
    g_debug_config.enable_logging = false;
}

// Main logging function
void debug_log(int level, const char *format, ...) {
    if (!g_debug_config.enable_logging || level > g_debug_config.log_level) {
        return;
    }
    
    if (g_log_file) {
        va_list args;
        va_start(args, format);
        
        fprintf(g_log_file, "[%s] ", get_timestamp());
        vfprintf(g_log_file, format, args);
        fprintf(g_log_file, "\n");
        fflush(g_log_file);  // Immediate write to disk
        
        va_end(args);
    }
}

// Log function entry
void debug_log_function_entry(const char *function_name, t_ps *data) {
    if (!g_debug_config.enable_logging) return;
    
    debug_log(DEBUG_DEBUG, "ENTRY: %s()", function_name);
    if (data) {
        debug_log_stack_state(data, "function entry");
    }
}

// Log function exit
void debug_log_function_exit(const char *function_name, t_ps *data) {
    if (!g_debug_config.enable_logging) return;
    
    debug_log(DEBUG_DEBUG, "EXIT: %s()", function_name);
    if (data) {
        debug_log_stack_state(data, "function exit");
    }
}

// Log operation execution
void debug_log_operation(const char *op_name, t_ps *data) {
    if (!g_debug_config.enable_logging) return;
    
    debug_log(DEBUG_DEBUG, "OPERATION: %s", op_name);
    if (data) {
        debug_log_stack_state(data, "after operation");
    }
}

// Log stack state
void debug_log_stack_state(t_ps *data, const char *context) {
    if (!g_debug_config.enable_logging || !data) return;
    
    debug_log(DEBUG_DEBUG, "STACK STATE (%s):", context);
    debug_log(DEBUG_DEBUG, "  Stack A: size=%d, top=%d, bottom=%d", 
              data->a.size, data->a.top, data->a.bottom);
    debug_log(DEBUG_DEBUG, "  Stack B: size=%d, top=%d, bottom=%d", 
              data->b.size, data->b.top, data->b.bottom);
    
    // Log ALL elements of each stack (no truncation)
    if (data->a.size > 0) {
        char a_elements[4096] = "";  // Increased buffer size for 100+ numbers
        size_t count = 0;
        int i = data->a.top;
        
        for (size_t j = 0; j < (size_t)data->a.size && count < sizeof(a_elements) - 20; j++) {
            count += snprintf(a_elements + count, sizeof(a_elements) - count, 
                             "%d ", data->a.stack[i]);
            i = (i + 1) % data->a.size;  // Use size instead of capacity
        }
        debug_log(DEBUG_DEBUG, "  Stack A elements: [%s]", a_elements);
    }
    
    if (data->b.size > 0) {
        char b_elements[4096] = "";  // Increased buffer size for 100+ numbers
        size_t count = 0;
        int i = data->b.top;
        
        for (size_t j = 0; j < (size_t)data->b.size && count < sizeof(b_elements) - 20; j++) {
            count += snprintf(b_elements + count, sizeof(b_elements) - count, 
                             "%d ", data->b.stack[i]);
            i = (i + 1) % data->b.size;  // Use size instead of capacity
        }
        debug_log(DEBUG_DEBUG, "  Stack B elements: [%s]", b_elements);
    }
}

// Log chunk state
void debug_log_chunk_state(t_chunk *chunk, const char *context) {
    if (!g_debug_config.enable_logging || !chunk) return;
    
    debug_log(DEBUG_DEBUG, "CHUNK STATE (%s):", context);
    debug_log(DEBUG_DEBUG, "  Location: %d, Size: %d", chunk->loc, chunk->size);
}

// NEW: Log variable change with line number
void debug_log_variable_change(const char *func_name, int line_num, t_ps *data, const char *var_name, const char *var_value) {
    if (!g_debug_config.enable_logging) return;
    
    debug_log(DEBUG_TRACE, "LINE %d in %s(): %s = %s", line_num, func_name, var_name, var_value);
    
    // Also log current stack state when variables change
    if (data) {
        debug_log_stack_state(data, "variable change");
    }
}

// NEW: Log complete line state
void debug_log_line_state(const char *func_name, int line_num, t_ps *data, const char *context) {
    if (!g_debug_config.enable_logging) return;
    
    debug_log(DEBUG_TRACE, "=== LINE %d in %s() === %s", line_num, func_name, context);
    
    if (data) {
        debug_log_all_variables(func_name, line_num, data, context);
    }
}

// NEW: Log before operation execution
void debug_log_before_operation(const char *func_name, int line_num, t_ps *data, const char *op_name) {
    if (!g_debug_config.enable_logging) return;
    
    debug_log(DEBUG_DEBUG, "BEFORE %s at LINE %d in %s()", op_name, line_num, func_name);
    
    if (data) {
        debug_log_stack_state(data, "before operation");
    }
}

// NEW: Log after operation execution
void debug_log_after_operation(const char *func_name, int line_num, t_ps *data, const char *op_name) {
    if (!g_debug_config.enable_logging) return;
    
    debug_log(DEBUG_DEBUG, "AFTER %s at LINE %d in %s()", op_name, line_num, func_name);
    
    if (data) {
        debug_log_stack_state(data, "after operation");
    }
}

// NEW: Log all variables in current scope
void debug_log_all_variables(const char *func_name, int line_num, t_ps *data, const char *context) {
    if (!g_debug_config.enable_logging || !data) return;
    
    debug_log(DEBUG_TRACE, "ALL VARIABLES at LINE %d in %s() - %s:", line_num, func_name, context);
    
    // Log stack A details
    debug_log(DEBUG_TRACE, "  Stack A: size=%d, top=%d, bottom=%d", 
              data->a.size, data->a.top, data->a.bottom);
    
    // Log stack B details  
    debug_log(DEBUG_TRACE, "  Stack B: size=%d, top=%d, bottom=%d", 
              data->b.size, data->b.top, data->b.bottom);
    
    // Log operation list info
    if (data->op_list) {
        int op_count = 0;
        t_list *current = data->op_list;
        while (current) {
            op_count++;
            current = current->next;
        }
        debug_log(DEBUG_TRACE, "  Operations in list: %d", op_count);
    }
    
    // Log writing mode
    debug_log(DEBUG_TRACE, "  Writing mode: %s", data->writing_mode ? "true" : "false");
    
    // Log ALL elements of each stack for complete visibility
    if (data->a.size > 0) {
        char a_elements[4096] = "";  // Increased buffer size for 100+ numbers
        int i = data->a.top;
        for (int j = 0; j < data->a.size; j++) {
            char temp[16];
            snprintf(temp, sizeof(temp), "%d ", data->a.stack[i]);
            strcat(a_elements, temp);
            i = (i + 1) % data->a.size;  // Use size for circular indexing
        }
        debug_log(DEBUG_TRACE, "  Stack A ALL elements: [%s]", a_elements);
    }
    
    if (data->b.size > 0) {
        char b_elements[4096] = "";  // Increased buffer size for 100+ numbers
        int i = data->b.top;
        for (int j = 0; j < data->b.size; j++) {
            char temp[16];
            snprintf(temp, sizeof(temp), "%d ", data->b.stack[i]);
            strcat(b_elements, temp);
            i = (i + 1) % data->b.size;  // Use size for circular indexing
        }
        debug_log(DEBUG_TRACE, "  Stack B ALL elements: [%s]", b_elements);
    }
}

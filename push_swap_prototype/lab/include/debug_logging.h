/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_logging.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: patrik <patrik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/24 18:45:00 by patrik            #+#    #+#              */
/*   Updated: 2025/08/24 18:45:00 by patrik           ###   ########.fr        */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEBUG_LOGGING_H
# define DEBUG_LOGGING_H

# include <time.h>
# include <stdbool.h>
# include "push_swap.h"

// Debug configuration
typedef struct s_debug_config {
    bool enable_logging;
    bool log_to_file;
    char *log_file_path;
    int log_level;
} t_debug_config;

// Log levels
# define DEBUG_ERROR   0
# define DEBUG_WARN    1
# define DEBUG_INFO    2
# define DEBUG_DEBUG   3
# define DEBUG_TRACE   4

// Debug snapshot structure (optimized for memory)
typedef struct s_debug_snapshot {
    char function_name[32];
    char timestamp[32];
    int a_top, a_bottom, a_size;
    int b_top, b_bottom, b_size;
    int chunk_sizes[4];  // TOP_A, BOTTOM_A, TOP_B, BOTTOM_B
    char context[64];
} t_debug_snapshot;

// Function declarations
void debug_init(const char *log_dir, int log_level);
void debug_cleanup(void);
void debug_log(int level, const char *format, ...);
void debug_log_function_entry(const char *function_name, t_ps *data);
void debug_log_function_exit(const char *function_name, t_ps *data);
void debug_log_operation(const char *op_name, t_ps *data);
void debug_log_stack_state(t_ps *data, const char *context);
void debug_log_chunk_state(t_chunk *chunk, const char *context);

// Macro for easy function logging
# define DEBUG_FUNC_ENTRY(data) debug_log_function_entry(__func__, data)
# define DEBUG_FUNC_EXIT(data) debug_log_function_exit(__func__, data)
# define DEBUG_OP(op, data) debug_log_operation(op, data)

// NEW: Automatic line-by-line logging macros
# define DEBUG_LINE(data, line_num) debug_log_line_state(__func__, line_num, data, #data)
# define DEBUG_VAR(data, var_name, var_value) debug_log_variable_change(__func__, __LINE__, data, var_name, var_value)
# define DEBUG_STACK_CHANGE(data, context) debug_log_stack_state(data, context)

// NEW: Automatic state capture before and after operations
# define DEBUG_BEFORE_OP(data, op_name) debug_log_before_operation(__func__, __LINE__, data, op_name)
# define DEBUG_AFTER_OP(data, op_name) debug_log_after_operation(__func__, __LINE__, data, op_name)

// NEW: Function to log variable changes
void debug_log_variable_change(const char *func_name, int line_num, t_ps *data, const char *var_name, const char *var_value);

// NEW: Function to log line state
void debug_log_line_state(const char *func_name, int line_num, t_ps *data, const char *context);

// NEW: Function to log before operation
void debug_log_before_operation(const char *func_name, int line_num, t_ps *data, const char *op_name);

// NEW: Function to log after operation
void debug_log_after_operation(const char *func_name, int line_num, t_ps *data, const char *op_name);

// NEW: Function to log all variables in current scope
void debug_log_all_variables(const char *func_name, int line_num, t_ps *data, const char *context);

#endif

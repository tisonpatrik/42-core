#ifndef CHUNK_UTILS_COMMON_H
# define CHUNK_UTILS_COMMON_H

// Forward declarations - models.h is already included in the .c files
struct s_stack;
typedef struct s_stack t_stack;
struct s_push_swap;
typedef struct s_push_swap t_ps;

// Helper function declarations
void init_stack(t_stack *stack, int size);
void cleanup_stack(t_stack *stack);
t_ps* create_test_data(int stack_a_size, int stack_b_size);
void cleanup_test_data(t_ps *data);

#endif

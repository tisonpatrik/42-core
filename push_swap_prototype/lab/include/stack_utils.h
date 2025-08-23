#ifndef STACK_UTILS_H
# define STACK_UTILS_H

// Forward declarations
struct s_stack;
typedef struct s_stack t_stack;
struct s_push_swap;
typedef struct s_push_swap t_ps;

// Stack management utilities
void init_stack(t_stack *stack, int size);
void cleanup_stack(t_stack *stack);

// Test data utilities
t_ps* create_test_data(int stack_a_size, int stack_b_size);
void cleanup_test_data(t_ps *data);

#endif

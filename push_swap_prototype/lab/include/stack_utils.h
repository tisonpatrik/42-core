#ifndef STACK_UTILS_H
# define STACK_UTILS_H

// Forward declarations
struct s_stack;
typedef struct s_stack t_stack;

// Stack management utilities
void init_stack(t_stack *stack, int size);
void cleanup_stack(t_stack *stack);

#endif

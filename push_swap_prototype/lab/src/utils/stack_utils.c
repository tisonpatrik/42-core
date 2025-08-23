#include "../../include/generator.h"
#include "../../libs/push_swap/src/models.h"
#include <stdlib.h>

// Stack initialization utility
void init_stack(t_stack *stack, int size) {
    int *random_data = generate_random_array(size);
    stack->stack = random_data;
    stack->size = size;
    stack->top = 0;
    stack->bottom = size - 1;
}

// Stack cleanup utility
void cleanup_stack(t_stack *stack) {
    if (stack->stack) {
        free(stack->stack);
        stack->stack = NULL;
    }
}

// Test data creation utility
t_ps* create_test_data(int stack_a_size, int stack_b_size) {
    t_ps *data = malloc(sizeof(t_ps));
    if (!data) return NULL;
    
    init_stack(&data->a, stack_a_size);
    init_stack(&data->b, stack_b_size);
    data->op_list = NULL;
    data->writing_mode = false;
    
    return data;
}

// Test data cleanup utility
void cleanup_test_data(t_ps *data) {
    if (data) {
        cleanup_stack(&data->a);
        cleanup_stack(&data->b);
        free(data);
    }
}

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

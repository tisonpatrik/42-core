
#include "../../include/stack.h"
#include <stdlib.h>

t_stack *create_stack(void)
{
    t_stack *stack = (t_stack *)malloc(sizeof(t_stack));
    if (!stack)
        return NULL;
    stack->head = NULL;
    stack->tail = NULL;
    stack->size = 0;
    return stack;
}

int get_size(t_stack *stack)
{
    if (!stack)
        return 0;
    return stack->size;
}

t_node *get_head(t_stack *stack)
{
    if (!stack)
        return NULL;
    return stack->head;
}

t_node *get_tail(t_stack *stack)
{
    if (!stack)
        return NULL;
    return stack->tail;
}




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

void clear_stack(t_stack *stack)
{
    t_node *current;
    t_node *next;
    
    if (!stack)
        return;
    
    // Traverse and free all nodes
    current = stack->head;
    while (current)
    {
        next = current->next;
        free(current);
        current = next;
    }
    
    // Reset stack state
    stack->head = NULL;
    stack->tail = NULL;
    stack->size = 0;
}

void fill_stack(t_stack *stack, int *numbers, int n)
{
    clear_stack(stack);
    t_node *node;
    int i = n - 1;
    
    while (i >= 0) {
        node = create_node(numbers[i]);
        push_to_stack(stack, node);
        i--;
    }
}


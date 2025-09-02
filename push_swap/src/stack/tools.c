#include "../../include/stack.h"
#include <stdlib.h>
#include <stdbool.h>

void clear_stack(t_stack *stack)
{
    t_node *current;
    t_node *next;
    
    if (!stack)
        return;
    
    // Traverse and free all nodes
    current = get_head(stack);
    while (current)
    {
        next = get_next(current);
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

bool is_sorted(t_stack *stack)
{
    t_node *current;
    t_node *next;
    
    if (!stack || get_size(stack) <= 1)
        return true;
    
    current = get_head(stack);
    next = get_next(current);
    
    while (next != NULL)
    {
        if (get_content(current) > get_content(next))
            return false;
        current = next;
        next = get_next(current);
    }
    return true;
}
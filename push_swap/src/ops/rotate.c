#include "../../include/ops.h"
#include <unistd.h>
#include <stdbool.h>

bool rotate(t_stack **stack)
{
    t_node *top_node;
    
    if (!stack || !*stack)
        return false;
    if (get_size(*stack) <= 1)
        return false;
    
    top_node = (*stack)->head;
    
    (*stack)->head = (*stack)->head->next;
    (*stack)->head->prev = NULL;
    
    top_node->next = NULL;
    top_node->prev = (*stack)->tail;
    (*stack)->tail->next = top_node;
    (*stack)->tail = top_node;
    
    return true;
}

// Shift up all elements of stack a by 1.
// The first element becomes the last one.
void rotate_a(t_sorting_state *state)
{
    bool success = rotate(&state->a);
    if (success)
        save_operation(state, RA);
}

// Shift up all elements of stack b by 1.
// The first element becomes the last one
void rotate_b(t_sorting_state *state)
{
    bool success = rotate(&state->b);
    if (success)
        save_operation(state, RB);
}

// Rotate both stacks a and b at the same time.
void rotate_ab(t_sorting_state *state)
{
    bool success_a = rotate(&state->a);
    bool success_b = rotate(&state->b);
    if (success_a && success_b)
        save_operation(state, RR);
}
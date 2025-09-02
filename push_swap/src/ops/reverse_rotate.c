#include "../../include/ops.h"
#include <unistd.h>
#include <stdbool.h>


bool reverse_rotate(t_stack **stack)
{
    t_node *bottom_node;
    t_node *head_node;
    t_node *prev_tail;
    
    if (!stack || !*stack)
        return false;
    if (get_size(*stack) <= 1)
        return false;
    
    bottom_node = get_tail(*stack);
    head_node = get_head(*stack);
    prev_tail = get_prev(bottom_node);
    
    (*stack)->tail = prev_tail;
    prev_tail->next = NULL;
    
    bottom_node->prev = NULL;
    bottom_node->next = head_node;
    head_node->prev = bottom_node;
    (*stack)->head = bottom_node;
    
    return true;
}

// Shift down all elements of stack a by 1.
// The last element becomes the first one
void reverse_rotate_a(t_sorting_state *state)
{
    bool success = reverse_rotate(&state->a);
    if (success)
        save_operation(state, RRA);
}

// Shift down all elements of stack b by 1.
// The last element becomes the first one.
void reverse_rotate_b(t_sorting_state *state)
{
    bool success = reverse_rotate(&state->b);
    if (success)
        save_operation(state, RRB);
}

// Reverse rotate both stacks a and b at the same time.
void reverse_rotate_ab(t_sorting_state *state)
{
    bool success_a = reverse_rotate(&state->a);
    bool success_b = reverse_rotate(&state->b);
    if (success_a && success_b)
        save_operation(state, RRR);
}
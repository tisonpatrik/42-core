#include "../../include/ops.h"
#include <unistd.h>
#include <stdbool.h>


bool reverse_rotate(t_stack **stack)
{
    t_node *bottom_node;
    
    if (!stack || !*stack)
        return false;
    if (get_size(*stack) <= 1)
        return false;
    
    // Get the bottom node
    bottom_node = (*stack)->tail;
    
    // Update tail to point to the previous node
    (*stack)->tail = (*stack)->tail->prev;
    (*stack)->tail->next = NULL;
    
    // Move bottom node to the top
    bottom_node->prev = NULL;
    bottom_node->next = (*stack)->head;
    (*stack)->head->prev = bottom_node;
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
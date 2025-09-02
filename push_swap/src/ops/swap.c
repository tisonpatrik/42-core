#include "../../include/ops.h"
#include <unistd.h>
#include <stdbool.h>

bool swap(t_stack **stack)
{
    int temp_content;
    t_node *first_node;
    t_node *second_node;
    
    if (!stack || !*stack)
        return false;
    if (get_size(*stack) < 2)
        return false;
    
    first_node = get_head(*stack);
    second_node = get_next(first_node);
    
    // Swap the content of the first two nodes
    temp_content = get_content(first_node);
    first_node->content = get_content(second_node);
    second_node->content = temp_content;
    
    return true;
}

// Swap the first 2 elements at the top of stack a.
// Do nothing if there is only one or no elements.
void swap_a(t_sorting_state *state)
{
    bool success = swap(&state->a);
    if (success)
        save_operation(state, SA);
}

// Swap the first 2 elements at the top of stack b.
// Do nothing if there is only one or no elements.
void swap_b(t_sorting_state *state)
{
    bool success = swap(&state->b);
    if (success)
        save_operation(state, SB);
}

// Swap the first 2 elements at the top of both stacks a and b.
// Do nothing if there is only one or no elements in either stack.
void swap_ab(t_sorting_state *state)
{
    bool success_a = swap(&state->a);
    bool success_b = swap(&state->b);
    if (success_a && success_b)
        save_operation(state, SS);
}
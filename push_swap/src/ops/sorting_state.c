

#include "../../include/ops.h"
#include <stdlib.h>

t_sorting_state *create_sorting_state(int *numbers, int n)
{
    t_sorting_state *state;
    t_stack *a;
    t_stack *b;
    
    if (!numbers || n <= 0)
        return NULL;
    
    state = malloc(sizeof(t_sorting_state));
    if (!state)
        return NULL;
    
    a = create_stack();
    b = create_stack();
    if (!a || !b)
    {
        if (a) clear_stack(a);
        if (b) clear_stack(b);
        free(state);
        return NULL;
    }
    
    fill_stack(a, numbers, n);
    
    state->a = a;
    state->b = b;
    state->operations = NULL;
    
    return state;
}

void free_sorting_state(t_sorting_state *state)
{
    if (!state)
        return;
    
    if (state->a)
    {
        clear_stack(state->a);
        free(state->a);
    }
    
    if (state->b)
    {
        clear_stack(state->b);
        free(state->b);
    }
    
    if (state->operations)
        ft_lstclear(&state->operations, free);
    
    free(state);
}

void save_operation(t_sorting_state *state, t_operation operation)
{
    t_list *new_node;
    int *op_ptr;
    
    if (!state)
        return;
    
    op_ptr = malloc(sizeof(int));
    if (!op_ptr)
        return;
    
    *op_ptr = operation;
    new_node = ft_lstnew(op_ptr);
    if (!new_node)
    {
        free(op_ptr);
        return;
    }
    
    ft_lstadd_back(&state->operations, new_node);
}
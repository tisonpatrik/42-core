#include <stdlib.h>
#include "../../include/ops.h"
#include "../../include/separator.h"

void push_non_lis_into_b(t_sorting_state *state)
{
    if (!state || !state->a)
        return;
    
    t_node_bool_array *lis_nodes = get_lis_nodes(state->a);
    if (!lis_nodes)
        return;
    
    int size_a = get_size(state->a);
    if (size_a <= 3)
        return;
    
    int min_b =0;
    int max_b =0;
    bool has_b_range = false;

    int i = 0;
    while (i < size_a)
    {
        int val = get_content(get_head(state->a));
        if (!has_b_range)
        {
            min_b = val;
            max_b = val;
            has_b_range = true;
        }
        else
        {
            if (val < min_b)
                min_b = val;
            if (val > max_b)
                max_b = val;
        }
        int mid = (min_b + max_b) / 2;
        if (val < mid)
        {
            rotate_b(state);
        }
    }


    free(lis_nodes->items);
    free(lis_nodes);
}
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
    
    free(lis_nodes->items);
    free(lis_nodes);
}
#include "../../include/stack.h"
#include "../../include/ops.h"
#include "../../include/separator.h"

void solve_push_swap(t_sorting_state *state)
{
   if (is_sorted(state->a))return;

    push_non_lis_into_b(state);
    return;
}
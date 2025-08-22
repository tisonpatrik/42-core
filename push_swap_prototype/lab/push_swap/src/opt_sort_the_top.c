#include "models.h"

int	next_down(t_stack *stk, int index);
int	next_up(t_stack *stk, int index);
int	current_size(t_stack *stk);

void	chunk_to_the_top(t_ps *data, t_chunk *to_sort)
{
	if (to_sort->loc == BOTTOM_B && current_size(&data->b) == to_sort->size)
		to_sort->loc = TOP_B;
	if (to_sort->loc == BOTTOM_A && current_size(&data->a) == to_sort->size)
		to_sort->loc = TOP_A;
}

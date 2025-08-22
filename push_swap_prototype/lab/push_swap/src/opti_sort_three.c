#include "models.h"

void	sort_three_top_a(t_ps *data, t_chunk *to_sort, t_stack *stk, int max);
void	sort_three_bottom_a(t_ps *data, t_chunk *to_sort, t_stack *stk, int max);
void	sort_three_top_b(t_ps *data, t_chunk *to_sort, t_stack *stk, int max);
void	sort_three_bottom_b(t_ps *data, t_chunk *to_sort, t_stack *stk, int max);
t_stack	*loc_to_stack(t_ps *data, t_loc loc);
int	chunk_max_value(t_ps *data, t_chunk *chunk);
void	swap_a(t_ps *data);
void	rotate_a(t_ps *data);
void	r_rotate_a(t_ps *data);
void	sort_two(t_ps *data, t_chunk *to_sort);
void	push_a(t_ps *data);
void	push_b(t_ps *data);
void	swap_b(t_ps *data);
void	r_rotate_b(t_ps *data);
int	next_down(t_stack *stk, int index);

void	sort_three(t_ps *data, t_chunk *to_sort)
{
	t_stack	*stk;
	int		max;

	stk = loc_to_stack(data, to_sort->loc);
	max = chunk_max_value(data, to_sort);
	if (to_sort->loc == TOP_A)
		sort_three_top_a(data, to_sort, stk, max);
	else if (to_sort->loc == BOTTOM_A)
		sort_three_bottom_a(data, to_sort, stk, max);
	else if (to_sort->loc == TOP_B)
		sort_three_top_b(data, to_sort, stk, max);
	else if (to_sort->loc == BOTTOM_B)
		sort_three_bottom_b(data, to_sort, stk, max);
}

void	sort_three_top_a(t_ps *data, t_chunk *to_sort, t_stack *stk, int max)
{
	if (stk->stack[stk->top] == max)
	{
		swap_a(data);
		rotate_a(data);
		swap_a(data);
		r_rotate_a(data);
	}
	else if (stk->stack[next_down(stk, stk->top)] == max)
	{
		rotate_a(data);
		swap_a(data);
		r_rotate_a(data);
	}
	to_sort->loc = TOP_A;
	to_sort->size -= 1;
	sort_two(data, to_sort);
}

void	sort_three_top_b(t_ps *data, t_chunk *to_sort, t_stack *stk, int max)
{
	push_a(data);
	if (stk->stack[stk->top] == max)
	{
		push_a(data);
		swap_a(data);
	}
	else if (stk->stack[next_down(stk, stk->top)] == max)
	{
		swap_b(data);
		push_a(data);
		swap_a(data);
	}
	else
		push_a(data);
	push_a(data);
	to_sort->loc = TOP_A;
	to_sort->size -= 1;
	sort_two(data, to_sort);
}

void	sort_three_bottom_a(t_ps *data, t_chunk *to_sort, t_stack *stk, int max)
{
	r_rotate_a(data);
	r_rotate_a(data);
	if (stk->stack[stk->top] == max)
	{
		swap_a(data);
		r_rotate_a(data);
	}
	else if (stk->stack[next_down(stk, stk->top)] == max)
		r_rotate_a(data);
	else
	{
		push_b(data);
		r_rotate_a(data);
		swap_a(data);
		push_a(data);
	}
	to_sort->loc = TOP_A;
	to_sort->size -= 1;
	sort_two(data, to_sort);
}

void	sort_three_bottom_b(t_ps *data, t_chunk *to_sort, t_stack *stk, int max)
{
	r_rotate_b(data);
	r_rotate_b(data);
	if (stk->stack[stk->top] == max)
	{
		push_a(data);
		r_rotate_b(data);
	}
	else if (stk->stack[next_down(stk, stk->top)] == max)
	{
		swap_b(data);
		push_a(data);
		r_rotate_b(data);
	}
	else
	{
		r_rotate_b(data);
		push_a(data);
	}
	to_sort->loc = TOP_B;
	to_sort->size -= 1;
	sort_two(data, to_sort);
}

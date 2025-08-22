#include "models.h"

void	save_op(t_ps *data, t_op op);

int	next_up(t_stack *stk, int index);
bool	is_full(t_stack *stk);
int	next_down(t_stack *stk, int index);

void	push(t_stack *src, t_stack *dest)
{
	int	dest_i;

	if (is_full(dest))
		return ;
	dest_i = next_up(dest, dest->top);
	dest->stack[dest_i] = src->stack[src->top];
	dest->top = dest_i;
	src->stack[src->top] = 0;
	src->top = next_down(src, src->top);
}

void	push_a(t_ps *data)
{
	push(&data->b, &data->a);
	if (data->writing_mode)
		save_op(data, pa);
}

void	push_b(t_ps *data)
{
	push(&data->a, &data->b);
	if (data->writing_mode)
		save_op(data, pb);
}
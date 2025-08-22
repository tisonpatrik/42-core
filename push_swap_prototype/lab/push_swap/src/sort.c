#include "models.h"

void	sort_three_a(t_ps *data);
void	sort_five_a(t_ps *data);
void	chunk_sort(t_ps *data);
void	post_sort_optimization(t_ps *data);
void	swap_a(t_ps *data);
void	rotate_a(t_ps *data);
void	r_rotate_a(t_ps *data);
void	swap_b(t_ps *data);
void	rotate_b(t_ps *data);
void	r_rotate_b(t_ps *data);
void	push_a(t_ps *data);
void	push_b(t_ps *data);

int	next_down(t_stack *stk, int index);
int	next_up(t_stack *stk, int index);
int	current_size(t_stack *stk);
int	value(t_stack *stk, int n);
bool	is_sorted(t_ps *data);


void	sort(t_ps *data)
{
	if (data->a.size <= 1 || is_sorted(data))
		return ;
	else if (data->a.size == 3)
		sort_three_a(data);
	else if (data->a.size == 5)
		sort_five_a(data);
	else
		chunk_sort(data);
	post_sort_optimization(data);
}

void	sort_three_a(t_ps *data)
{
	int	first;
	int	second;
	int	third;

	first = value(&data->a, 1);
	second = value(&data->a, 2);
	third = value(&data->a, 3);
	if (first > second && third > second && third > first)
		swap_a(data);
	else if (first > second && third > second && first > third)
		rotate_a(data);
	else if (second > first && second > third && first > third)
		r_rotate_a(data);
	else if (second > first && second > third && third > first)
	{
		swap_a(data);
		rotate_a(data);
	}
	else if (first > second && second > third && first > third)
	{
		swap_a(data);
		r_rotate_a(data);
	}
}

void	sort_five_a(t_ps *data)
{
	while (current_size(&data->a) > 3)
	{
		if (value(&data->a, 1) == 1 || value(&data->a, 1) == 2)
			push_b(data);
		else
			rotate_a(data);
	}
	if (value(&data->b, 1) < value(&data->b, 2))
		swap_b(data);
	sort_three_a(data);
	push_a(data);
	push_a(data);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   opti_sort_asap.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: patrik <patrik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 20:58:30 by ugerkens          #+#    #+#             */
/*   Updated: 2025/08/25 14:51:53 by patrik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/push_swap.h"

void	split_max_reduction(t_ps *data, t_chunk *max)
{
	t_stack	*a;

	a = &data->a;

	if (max->loc == TOP_A && max->size == 3 && is_consecutive(value(a, 1),
			value(a, 2), value(a, 3), value(a, 4)) && a_partly_sort(data, 4))
	{
		sort_three(data, max);
		return ;
	}

	if (max->loc == TOP_A && value(a, 1) == value(a, 3) - 1
		&& a_partly_sort(data, 3))
	{
		swap_a(data);
		max->size--;
	}
	
	if (max->loc == TOP_A && a_partly_sort(data, 1))
	{
		max->size--;
	}
	
}

bool	a_partly_sort(t_ps *data, int from)
{
	int		i;
	t_stack	*a;
	int		value;

	a = &data->a;
	
	// First loop: move to the starting position
	for (i = a->top; from > 0; from--)
	{
		i = next_down(a, i);
	}
	
	// Second loop: check if the sequence is sorted
	value = a->stack[i];
	for (; a->stack[i] != data->a.size; i = next_down(a, i))
	{
		if (a->stack[i] != value + 1)
		{
			return (false);
		}
		value = a->stack[i];
	}
	
	return (true);
}
bool	is_consecutive(int a, int b, int c, int d)
{
	sort_three_numbers(&a, &b, &c);
	
	bool result = ((b - a == 1) && (c - b == 1) && (d - c == 1));
	
	return (result);
}

void	sort_three_numbers(int *a, int *b, int *c)
{
	int	temp;

	if (*a > *b)
	{
		temp = *a;
		*a = *b;
		*b = temp;
	}
	if (*a > *c)
	{
		temp = *a;
		*a = *c;
		*c = temp;
	}
	if (*b > *c)
	{
		temp = *b;
		*b = *c;
		*c = temp;
	}	
}

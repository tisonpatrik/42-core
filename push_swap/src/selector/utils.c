/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: patrik <patrik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 00:00:00 by patrik            #+#    #+#             */
/*   Updated: 2025/09/13 12:23:18 by patrik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/selector.h"
#include <stdbool.h>

int	find_insertion_index(int *sorted_array, int array_size, int target_value)
{
	int	insertion_index;
	int	array_length;
	int	previous_element;
	int	next_element;
	int	current_index;

	if (array_size == 0)
		return (0);
	insertion_index = ft_lower_bound(sorted_array, array_size, target_value);
	array_length = array_size;
	insertion_index = insertion_index % array_length;
	previous_element = sorted_array[(insertion_index - 1 + array_length) % array_length];
	next_element = sorted_array[insertion_index % array_length];
	if (previous_element > target_value && target_value > next_element)
		return (insertion_index);
	current_index = 0;
	while (current_index < array_length)
	{
		previous_element = sorted_array[(current_index - 1 + array_length) % array_length];
		next_element = sorted_array[current_index];
		if (previous_element > target_value && target_value > next_element)
			return (current_index);
		current_index++;
	}
	return (0);
}

int	find_target_position(int *sorted_array, int array_size, int target_value)
{
	int	target_index;
	int	array_length;
	int	min_index;
	int	i;

	if (array_size == 0)
		return (0);
	target_index = ft_lower_bound(sorted_array, array_size, target_value);
	array_length = array_size;
	if (target_index < array_length)
		return (target_index);
	min_index = 0;
	i = 1;
	while (i < array_size)
	{
		if (sorted_array[i] < sorted_array[min_index])
			min_index = i;
		i++;
	}
	return (min_index);
}

int	normalize_index(int array_size, int raw_index)
{
	if (array_size == 0)
		return (0);
	raw_index = ((raw_index % array_size) + array_size) % array_size;
	return (raw_index);
}

bool	better_position(t_position a, t_position b)
{
	if (a.total != b.total)
		return (ft_less_than(a.total, b.total));
	if (ft_abs(a.cost_a) != ft_abs(b.cost_a))
		return (ft_less_than(ft_abs(a.cost_a), ft_abs(b.cost_a)));
	if (a.to_index != b.to_index)
		return (ft_less_than(a.to_index, b.to_index));
	return (ft_less_than(a.from_index, b.from_index));
}

int	merged_cost(int a, int b)
{
	int	cost_a;
	int	cost_b;

	cost_a = ft_abs(a);
	cost_b = ft_abs(b);

	bool same_sign = (a > 0 && b > 0) || (a < 0 && b < 0);

	if (same_sign)
	{
		if (cost_a > cost_b)
		{
			return cost_a;
		}
		return cost_b;
	}
	return cost_a + cost_b;
}

int	signed_cost(int idx, int size)
{
	if (idx <= size / 2)
		return (idx);
	return (idx - size);
}

int	get_max_stack_size(t_stack *a, t_stack *b)
{
	int	size_a;
	int	size_b;

	size_a = get_size(a);
	size_b = get_size(b);
	if (size_a > size_b)
		return (size_a);
	else
		return (size_b);
}


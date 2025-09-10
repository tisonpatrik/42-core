/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: patrik <patrik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 21:41:22 by patrik            #+#    #+#             */
/*   Updated: 2025/09/10 23:03:59 by patrik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../../include/selector.h"

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

	if (array_size == 0)
		return (0);
	target_index = ft_lower_bound(sorted_array, array_size, target_value);
	array_length = array_size;
	if (target_index < array_length)
		return (target_index);
	return (0);
}

int	normalize_index(int array_size, int raw_index)
{
	if (array_size == 0)
		return (0);
	raw_index = ((raw_index % array_size) + array_size) % array_size;
	return (raw_index);
}

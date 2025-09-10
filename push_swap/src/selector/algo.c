/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: patrik <patrik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 21:41:22 by patrik            #+#    #+#             */
/*   Updated: 2025/09/10 22:44:33 by patrik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../../include/selector.h"

int	binary_search_insertion_point(int *sorted_array, int array_size, int target_value, 
	bool (*comparator)(int, int))
{
	int	left_bound;
	int	right_bound;
	int	middle_index;

	if (array_size == 0)
		return (0);
	left_bound = 0;
	right_bound = array_size;
	while (left_bound < right_bound)
	{
		middle_index = (left_bound + right_bound) / 2;
		if (comparator(sorted_array[middle_index], target_value))
			left_bound = middle_index + 1;
		else
			right_bound = middle_index;
	}
	return (left_bound);
}

int	find_insertion_index(int *sorted_array, int array_size, int target_value)
{
	int	insertion_index;
	int	array_length;
	int	previous_element;
	int	next_element;
	int	current_index;

	if (array_size == 0)
		return (0);
	insertion_index = binary_search_insertion_point(sorted_array, array_size, target_value, ft_less_than);
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
	target_index = binary_search_insertion_point(sorted_array, array_size, target_value, ft_less_than_or_equal);
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

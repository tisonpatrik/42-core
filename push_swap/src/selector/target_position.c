/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   target_position.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: patrik <patrik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/17 22:25:26 by ptison            #+#    #+#             */
/*   Updated: 2025/09/22 11:08:46 by patrik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/selector.h"

/*
 * Finds the smallest element greater than the target value.
 *
 * This function searches through the array to find the element that is
 * just larger than the target value. If multiple elements are greater
 * than the target, it selects the smallest one among them.
 *
 * This is used to determine where an element should be inserted to
 * maintain sorted order in the target array.
 *
 * @param array: Sorted array to search in
 * @param array_size: Number of elements in the array
 * @param target_value: Value to find insertion point for
 * @return: Index of smallest element greater than target, or -1 if none found
 */
static int	find_smallest_greater_than(int *array, int array_size,
		int target_value)
{
	int	best_idx;
	int	best_val;
	int	i;

	best_idx = -1;
	best_val = 0;
	i = 0;
	while (i < array_size)
	{
		if (array[i] > target_value)
		{
			if (best_idx == -1 || array[i] < best_val)
			{
				best_val = array[i];
				best_idx = i;
			}
		}
		i++;
	}
	return (best_idx);
}

/*
 * Finds the index of the minimum element in the array.
 *
 * This function searches through the entire array to find the element
 * with the smallest value and returns its index. This is used as a
 * fallback when no element is greater than the target value.
 *
 * @param array: Array to search in
 * @param array_size: Number of elements in the array
 * @return: Index of the minimum element
 */
static int	find_minimum_index(int *array, int array_size)
{
	int	min_idx;
	int	min_val;
	int	i;

	min_idx = 0;
	min_val = array[0];
	i = 1;
	while (i < array_size)
	{
		if (array[i] < min_val)
		{
			min_val = array[i];
			min_idx = i;
		}
		i++;
	}
	return (min_idx);
}

/*
 * Finds the optimal target position for inserting a value into a sorted array.
 *
 * This function determines where a value should be inserted to maintain
 * the sorted order of the array. The algorithm:
 * 1. First tries to find the smallest element greater than the target
 * 2. If no such element exists, falls back to the minimum element position
 *
 * This ensures that the insertion maintains the circular sorted order
 * of the stack, which is crucial for the push_swap algorithm.
 *
 * @param array: Sorted array representing stack A
 * @param array_size: Number of elements in the array
 * @param target_value: Value to find insertion position for
 * @return: Index where the value should be inserted
 */
int	find_target_position(int *array, int array_size, int target_value)
{
	int	best_idx;

	if (array_size == 0)
		return (0);
	best_idx = find_smallest_greater_than(array, array_size, target_value);
	if (best_idx != -1)
		return (best_idx);
	return (find_minimum_index(array, array_size));
}

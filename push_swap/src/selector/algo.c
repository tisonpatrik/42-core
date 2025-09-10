/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: patrik <patrik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 21:41:22 by patrik            #+#    #+#             */
/*   Updated: 2025/09/10 21:41:23 by patrik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../../include/selector.h"

// Helper comparator functions for binary search
static bool	less_than(int arr_val, int target_val)
{
	return (arr_val < target_val);
}

static bool	less_than_or_equal(int arr_val, int target_val)
{
	return (arr_val <= target_val);
}

// BinarySearchInsertionPoint performs binary search to find insertion point for a value
// using a custom comparator function
int	binary_search_insertion_point(int *arr, int size, int val, 
	bool (*comparator)(int, int))
{
	int	left;
	int	right;
	int	mid;

	if (size == 0)
		return (0);
	left = 0;
	right = size;
	while (left < right)
	{
		mid = (left + right) / 2;
		if (comparator(arr[mid], val))
			left = mid + 1;
		else
			right = mid;
	}
	return (left);
}

// FindInsertionIndex finds the insertion index in a sorted descending array (stack B)
// maintaining local order "prev > val > next"
int	find_insertion_index(int *sorted_arr, int size, int val)
{
	int	idx;
	int	n;
	int	prev;
	int	next;
	int	j;

	if (is_empty(sorted_arr, size))
		return (0);
	// Binary search for insertion point in sorted descending array
	idx = binary_search_insertion_point(sorted_arr, size, val, less_than);
	n = size;
	idx = idx % n;
	// Check circular neighbors for proper local order
	prev = sorted_arr[(idx - 1 + n) % n];
	next = sorted_arr[idx % n];
	if (prev > val && val > next)
		return (idx);
	// Fallback to linear search if binary search doesn't find exact position
	j = 0;
	while (j < n)
	{
		prev = sorted_arr[(j - 1 + n) % n];
		next = sorted_arr[j];
		if (prev > val && val > next)
			return (j);
		j++;
	}
	return (0);
}

// FindTargetPosition finds the target position in a sorted ascending array (stack A)
// for inserting a value to maintain ascending order
int	find_target_position(int *sorted_arr, int size, int val)
{
	int	idx;
	int	n;

	if (is_empty(sorted_arr, size))
		return (0);
	// Binary search for the first element > val
	idx = binary_search_insertion_point(sorted_arr, size, val, less_than_or_equal);
	n = size;
	if (idx < n)
		return (idx);
	// If val >= all elements, return index of minimum (0 in sorted ascending stack)
	return (0);
}

// NormalizeIndex normalizes an index to be within bounds [0, n)
int	normalize_index(int n, int k)
{
	if (n == 0)
		return (0);
	k = ((k % n) + n) % n;
	return (k);
}

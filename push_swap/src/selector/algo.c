/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: patrik <patrik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 21:41:22 by patrik            #+#    #+#             */
/*   Updated: 2025/09/10 22:26:32 by patrik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../../include/selector.h"

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

int	find_insertion_index(int *sorted_arr, int size, int val)
{
	int	idx;
	int	n;
	int	prev;
	int	next;
	int	j;

	if (is_empty(sorted_arr, size))
		return (0);
	idx = binary_search_insertion_point(sorted_arr, size, val, ft_less_than);
	n = size;
	idx = idx % n;
	prev = sorted_arr[(idx - 1 + n) % n];
	next = sorted_arr[idx % n];
	if (prev > val && val > next)
		return (idx);
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

int	find_target_position(int *sorted_arr, int size, int val)
{
	int	idx;
	int	n;

	if (is_empty(sorted_arr, size))
		return (0);
	idx = binary_search_insertion_point(sorted_arr, size, val, ft_less_than_or_equal);
	n = size;
	if (idx < n)
		return (idx);
	return (0);
}

int	normalize_index(int n, int k)
{
	if (n == 0)
		return (0);
	k = ((k % n) + n) % n;
	return (k);
}

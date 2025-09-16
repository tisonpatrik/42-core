/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lower_bound.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: patrik <patrik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 22:05:29 by patrik            #+#    #+#             */
/*   Updated: 2025/09/16 21:19:14 by ptison           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/search.h"

/**
 * @brief Finds the lower bound of a value in a sorted array
 *
 * This function finds the first position in a sorted array where the given
 * value could be inserted while maintaining the sorted order. It uses binary
 * search for O(log n) time complexity.
 *
 * @param arr Sorted array to search in
 * @param n Number of elements in the array
 * @param x Value to find the lower bound for
 * @return Index of the lower bound position
 */
int	ft_lower_bound(const int *arr, int n, int x)
{
	int	left;
	int	right;
	int	mid;

	left = 0;
	right = n;
	while (left < right)
	{
		mid = left + (right - left) / 2;
		if (arr[mid] < x)
			left = mid + 1;
		else
			right = mid;
	}
	return (left);
}

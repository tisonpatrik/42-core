/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_heap_sort.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: patrik <patrik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 22:04:54 by patrik            #+#    #+#             */
/*   Updated: 2025/09/10 22:07:04 by patrik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../../include/sort.h"
#include "../../include/math.h"

/**
 * @brief Performs heapify operation for heap sort
 *
 * This is a helper function for heap sort that maintains the heap property
 * by sifting down an element to its correct position in the heap.
 *
 * @param arr Array to heapify
 * @param n Size of the heap
 * @param i Index of the element to sift down
 */
static void	sift_down(int *arr, int n, int i)
{
	int	left;
	int	right;
	int	largest;

	while (1)
	{
		left = 2 * i + 1;
		right = 2 * i + 2;
		largest = i;
		if (left < n && arr[left] > arr[largest])
			largest = left;
		if (right < n && arr[right] > arr[largest])
			largest = right;
		if (largest == i)
			break ;
		ft_swap_int(&arr[i], &arr[largest]);
		i = largest;
	}
}

/**
 * @brief Sorts an array using heap sort algorithm
 *
 * This function sorts an array of integers in ascending order using the
 * heap sort algorithm. Heap sort has O(n log n) time complexity and
 * O(1) space complexity.
 *
 * @param arr Array to sort
 * @param n Number of elements in the array
 */
void	ft_heap_sort(int *arr, int n)
{
	int	i;
	int	end;

	if (!arr || n <= 1)
		return ;
	i = n / 2 - 1;
	while (i >= 0)
	{
		sift_down(arr, n, i);
		i--;
	}
	end = n - 1;
	while (end > 0)
	{
		ft_swap_int(&arr[0], &arr[end]);
		sift_down(arr, end, 0);
		end--;
	}
}

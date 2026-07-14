/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_heap_sort.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omaly <student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 22:04:54 by ptison            #+#    #+#             */
/*   Updated: 2026/02/26 11:33:39 by omaly            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/sort.h"

static void	swap_ptr(void **a, void **b)
{
	void	*tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
}

static void	sift_down(void **arr, size_t n, size_t i, int (*cmp)(void *,
			void *))
{
	size_t	left;
	size_t	right;
	size_t	largest;

	while (1)
	{
		left = 2 * i + 1;
		right = 2 * i + 2;
		largest = i;
		if (left < n && cmp(arr[left], arr[largest]) > 0)
			largest = left;
		if (right < n && cmp(arr[right], arr[largest]) > 0)
			largest = right;
		if (largest == i)
			break ;
		swap_ptr(&arr[i], &arr[largest]);
		i = largest;
	}
}

void	ft_heap_sort_ptr(void **arr, size_t n, int (*cmp)(void *, void *))
{
	ssize_t	i;
	size_t	end;

	if (!arr || n <= 1)
		return ;
	i = n / 2 - 1;
	while (i >= 0)
	{
		sift_down(arr, n, (size_t)i, cmp);
		i--;
	}
	end = n - 1;
	while (end > 0)
	{
		swap_ptr(&arr[0], &arr[end]);
		sift_down(arr, end, 0, cmp);
		end--;
	}
}

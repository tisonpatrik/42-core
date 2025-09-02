/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   normalization.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: patrik <patrik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/17 17:59:38 by ptison            #+#    #+#             */
/*   Updated: 2025/09/02 13:45:22 by patrik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/validator.h"
#include <stdlib.h>

void	swap_int(int *a, int *b)
{
	int	t;

	t = *a;
	*a = *b;
	*b = t;
}

void	sift_down(int *a, int n, int i)
{
	int	l;
	int	r;
	int	largest;

	while (1)
	{
		l = 2 * i + 1;
		r = 2 * i + 2;
		largest = i;
		if (l < n && a[l] > a[largest])
			largest = l;
		if (r < n && a[r] > a[largest])
			largest = r;
		if (largest == i)
			break ;
		swap_int(&a[i], &a[largest]);
		i = largest;
	}
}

void	heap_sort(int *a, int n)
{
	int	i;
	int	end;

	i = n / (2 - 1);
	while (i >= 0)
	{
		sift_down(a, n, i);
		i--;
	}
	end = n - 1;
	while (end > 0)
	{
		swap_int(&a[0], &a[end]);
		sift_down(a, end, 0);
		end--;
	}
}

int	lower_bound(const int *a, int n, int x)
{
	int	lo;
	int	hi;
	int	mid;

	lo = 0;
	hi = n;
	while (lo < hi)
	{
		mid = lo + (hi - lo) / 2;
		if (a[mid] < x)
			lo = mid + 1;
		else
			hi = mid;
	}
	return (lo);
}

int	*indexize_array(const int *values, int n)
{
	int	*sorted;
	int	*res;
	int	i;

	if (!values || n <= 0)
		return (NULL);
	sorted = malloc(sizeof(int) * n);
	if (!sorted)
		return (NULL);
	ft_memcpy(sorted, values, (size_t)n * sizeof values[0]);
	heap_sort(sorted, n);
	res = malloc(sizeof(int) * n);
	if (!res)
	{
		free(sorted);
		return (NULL);
	}
	i = 0;
	while (i < n)
	{
		res[i] = lower_bound(sorted, n, values[i]);
		i++;
	}
	free(sorted);
	return (res);
}

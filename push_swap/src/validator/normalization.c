/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   normalization.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptison <ptison@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/17 17:59:38 by ptison            #+#    #+#             */
/*   Updated: 2025/10/04 14:21:12 by ptison           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/validator.h"
#include <stdlib.h>

/*
 * Checks if the array is already indexed (contains values 0, 1, 2, ..., n-1).
 * 
 * @param values: Array to check
 * @param n: Number of elements in the array
 * @return: true if already indexed, false otherwise
 */
static bool	is_already_indexed(const int *values, int n)
{
	int	i;

	i = 0;
	while (i < n)
	{
		if (values[i] != i)
			return (false);
		i++;
	}
	return (true);
}

/*
 * Performs the actual indexing of the array by sorting and mapping values to indices.
 * 
 * @param values: Array to index
 * @param n: Number of elements in the array
 * @return: New indexed array or NULL on failure
 */
static int	*perform_indexing(const int *values, int n)
{
	int	*sorted;
	int	*res;
	int	i;

	sorted = malloc(sizeof(int) * n);
	if (!sorted)
		return (NULL);
	ft_memcpy(sorted, values, (size_t)n * sizeof values[0]);
	ft_heap_sort(sorted, n);
	res = malloc(sizeof(int) * n);
	if (!res)
	{
		free(sorted);
		return (NULL);
	}
	i = 0;
	while (i < n)
	{
		res[i] = ft_lower_bound(sorted, n, values[i]);
		i++;
	}
	free(sorted);
	return (res);
}

/*
 * Orchestrates the indexing process by first validating if indexing is needed,
 * then performing the indexing if necessary.
 * 
 * @param values: Array to index
 * @param n: Number of elements in the array
 * @return: Indexed array or NULL on failure
 */
int	*indexize_array(const int *values, int n)
{
	int	*res;

	if (!values || n <= 0)
		return (NULL);
	
	if (is_already_indexed(values, n))
	{
		res = malloc(sizeof(int) * n);
		if (!res)
			return (NULL);
		ft_memcpy(res, values, (size_t)n * sizeof values[0]);
		return (res);
	}
	
	return (perform_indexing(values, n));
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   normalization.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: patrik <patrik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/17 17:59:38 by ptison            #+#    #+#             */
/*   Updated: 2025/09/16 22:16:21 by patrik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/validator.h"
#include <stdlib.h>

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

void	fatal_cleanup_and_exit(int *buf, char **tmp)
{
	if (buf)
		free(buf);
	if (tmp)
		ft_free_array(tmp);
	ft_putstr_fd("Error\n", 2);
	exit(1);
}

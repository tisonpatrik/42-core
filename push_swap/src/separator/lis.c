/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lis.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptison <ptison@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 18:49:46 by ptison            #+#    #+#             */
/*   Updated: 2025/09/09 18:56:11 by ptison           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/separator.h"
#include "../../include/stack.h"
#include <stdbool.h>
#include <stdlib.h>

void	cleanup_tmp(t_node **nodes, int *vals, int *lis, int *prev)
{
	free(nodes);
	free(vals);
	free(lis);
	free(prev);
}

static int	fill_nodes_vals(t_stack *stack, t_node **nodes, int *vals, int n)
{
	t_node	*cur;
	int		i;

	cur = get_head(stack);
	i = 0;
	while (i < n)
	{
		nodes[i] = cur;
		vals[i] = get_content(cur);
		cur = get_next(cur);
		i++;
	}
	return (0);
}

static void	compute_lis_prev(int *vals, int n, int *lis, int *prev,
		int *best_len, int *best_end)
{
	int	i;
	int	j;

	*best_len = 0;
	*best_end = 0;
	i = 0;
	while (i < n)
	{
		lis[i] = 1;
		prev[i] = -1;
		j = 0;
		while (j < i)
		{
			if (vals[j] < vals[i] && lis[j] + 1 > lis[i])
			{
				lis[i] = lis[j] + 1;
				prev[i] = j;
			}
			j++;
		}
		if (lis[i] >= *best_len)
		{
			*best_len = lis[i];
			*best_end = i;
		}
		i++;
	}
}

static t_node_bool_array	*build_result_and_reverse(t_node **nodes, int *prev,
		int best_end, int best_len)
{
	t_node_bool_array	*result;
	size_t				k;
	size_t				l;
	int					i;
	t_node_bool			tmp;

	result = malloc(sizeof(*result));
	if (!result)
		return (NULL);
	result->items = calloc((size_t)best_len, sizeof(t_node_bool));
	if (!result->items)
	{
		free(result);
		return (NULL);
	}
	k = 0;
	i = best_end;
	while (i != -1 && k < (size_t)best_len)
	{
		result->items[k].node = nodes[i];
		result->items[k].value = true;
		k++;
		i = prev[i];
	}
	result->count = k;
	l = 0;
	while (l < result->count / 2)
	{
		tmp = result->items[l];
		result->items[l] = result->items[result->count - 1 - l];
		result->items[result->count - 1 - l] = tmp;
		l++;
	}
	return (result);
}

t_node_bool_array	*get_lis_nodes(t_stack *stack)
{
	int					n;
	t_node				**nodes;
	int					*vals;
	int					*lis;
	int					*prev;
	int					best_len;
	int					best_end;
	t_node_bool_array	*result;

	n = get_size(stack);
	if (n <= 0)
	{
		result = malloc(sizeof(*result));
		if (!result)
			return (NULL);
		result->items = NULL;
		result->count = 0;
		return (result);
	}
	nodes = malloc(sizeof(*nodes) * (size_t)n);
	vals = malloc(sizeof(*vals) * (size_t)n);
	if (!nodes || !vals)
		return (free(nodes), free(vals), NULL);
	fill_nodes_vals(stack, nodes, vals, n);
	lis = malloc(sizeof(*lis) * (size_t)n);
	prev = malloc(sizeof(*prev) * (size_t)n);
	if (!lis || !prev)
		return (free(lis), free(prev), free(nodes), free(vals), NULL);
	compute_lis_prev(vals, n, lis, prev, &best_len, &best_end);
	result = build_result_and_reverse(nodes, prev, best_end, best_len);
	cleanup_tmp(nodes, vals, lis, prev);
	return (result);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lis_helpers.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: patrik <patrik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 18:49:46 by ptison            #+#    #+#             */
/*   Updated: 2025/09/09 19:33:25 by patrik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/separator.h"
#include "../../include/stack.h"
#include <stdbool.h>
#include <stdlib.h>

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

static void	compute_lis_prev(t_lis_computation_data *data, t_lis_result *result)
{
	int	i;
	int	j;

	result->best_len = 0;
	result->best_end = 0;
	i = 0;
	while (i < data->n)
	{
		data->lis[i] = 1;
		data->prev[i] = -1;
		j = 0;
		while (j < i)
		{
			if (data->vals[j] < data->vals[i]
				&& data->lis[j] + 1 > data->lis[i])
			{
				data->lis[i] = data->lis[j] + 1;
				data->prev[i] = j;
			}
			j++;
		}
		if (data->lis[i] >= result->best_len)
		{
			result->best_len = data->lis[i];
			result->best_end = i;
		}
		i++;
	}
}

static t_node_bool_array	*build_result_and_reverse(t_node **nodes, int *prev,
		int best_end, int best_len)
{
	t_node_bool_array	*result;
	size_t				k;
	int					i;
	size_t				l;
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

static t_node_bool_array	*allocate_arrays(t_allocation_data *data)
{
	*data->nodes = malloc(sizeof(**data->nodes) * (size_t)data->n);
	*data->vals = malloc(sizeof(**data->vals) * (size_t)data->n);
	if (!*data->nodes || !*data->vals)
		return (free(*data->nodes), free(*data->vals), NULL);
	*data->lis = malloc(sizeof(**data->lis) * (size_t)data->n);
	*data->prev = malloc(sizeof(**data->prev) * (size_t)data->n);
	if (!*data->lis || !*data->prev)
		return (free(*data->lis), free(*data->prev),
			free(*data->nodes), free(*data->vals), NULL);
	return ((t_node_bool_array *)1);
}

static t_node_bool_array	*process_lis_computation(t_stack *stack, int n)
{
	t_node					**nodes;
	int						*vals;
	int						*lis;
	int						*prev;
	t_lis_result			lis_result;
	t_node_bool_array		*result;
	t_lis_computation_data	comp_data;
	t_allocation_data		alloc_data;

	alloc_data.n = n;
	alloc_data.nodes = &nodes;
	alloc_data.vals = &vals;
	alloc_data.lis = &lis;
	alloc_data.prev = &prev;
	if (!allocate_arrays(&alloc_data))
		return (NULL);
	fill_nodes_vals(stack, nodes, vals, n);
	comp_data.vals = vals;
	comp_data.n = n;
	comp_data.lis = lis;
	comp_data.prev = prev;
	compute_lis_prev(&comp_data, &lis_result);
	result = build_result_and_reverse(nodes, prev, lis_result.best_end,
			lis_result.best_len);
	free(nodes);
	free(vals);
	free(lis);
	free(prev);
	return (result);
}

t_node_bool_array	*get_lis_nodes_impl(t_stack *stack, int n)
{
	t_node_bool_array	*result;

	if (n <= 0)
	{
		result = malloc(sizeof(*result));
		if (!result)
			return (NULL);
		result->items = NULL;
		result->count = 0;
		return (result);
	}
	return (process_lis_computation(stack, n));
}

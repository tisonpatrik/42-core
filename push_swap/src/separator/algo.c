/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: patrik <patrik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 19:25:49 by patrik            #+#    #+#             */
/*   Updated: 2025/09/19 23:04:57 by patrik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/separator.h"
#include "../../include/stack.h"
#include <stdbool.h>

static t_node	**execute_lis_algorithm(t_stack *stack,
		t_separator_arena *arena)
{
	t_lis_result	result;

	extract_stack_values_to_computation(stack, arena->computation);
	compute_longest_increasing_lens(arena->computation, &result);
	return (build_lis_result(arena->computation, &result, arena));
}

static void	get_empty_result(t_node **lis_nodes)
{
	if (!lis_nodes)
		return ;
}

t_node	**get_lis_nodes(t_stack *stack, t_separator_arena *arena)
{
	int	stack_size;

	stack_size = get_size(stack);
	if (stack_size <= 0)
	{
		get_empty_result(arena->lis_nodes);
		return (arena->lis_nodes);
	}
	return (execute_lis_algorithm(stack, arena));
}

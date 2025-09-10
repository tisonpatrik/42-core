/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cost_calculator.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: patrik <patrik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 21:41:15 by patrik            #+#    #+#             */
/*   Updated: 2025/09/10 21:49:44 by patrik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../../include/selector.h"

t_cost_calculator	*new_cost_calculator(t_selector_config config)
{
	t_cost_calculator	*calc;

	calc = malloc(sizeof(t_cost_calculator));
	if (!calc)
		return (NULL);
	calc->config = config;
	return (calc);
}

void	free_cost_calculator(t_cost_calculator *calc)
{
	if (calc)
		free(calc);
}

t_position	calculate_position_cost(t_cost_calculator *calc, int from_idx, 
	int to_idx, int size_a, int size_b)
{
	t_position	position;
	int			cost_a;
	int			cost_b;
	int			base;

	cost_a = signed_cost(from_idx, size_a);
	cost_b = signed_cost(to_idx, size_b);
	base = calculate_merged_cost(calc, cost_a, cost_b);
	position.from_index = from_idx;
	position.to_index = to_idx;
	position.cost_a = cost_a;
	position.cost_b = cost_b;
	position.total = base;
	return (position);
}

int	calculate_penalty(t_cost_calculator *calc, int *stack, int size, 
	int to_idx, int val)
{
	int	n;
	int	prev;
	int	next;

	(void)calc; // Unused parameter
	if (is_empty_or_single(stack, size))
		return (0);
	n = size;
	prev = stack[(to_idx - 1 + n) % n];
	next = stack[to_idx % n];
	if (prev > val && val > next)
		return (0);
	return (1);
}

int	calculate_merged_cost(t_cost_calculator *calc, int cost_a, int cost_b)
{
	(void)calc; // Unused parameter
	return (merged_cost(cost_a, cost_b));
}

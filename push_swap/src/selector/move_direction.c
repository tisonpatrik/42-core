/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_direction.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: patrik <patrik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 21:41:06 by patrik            #+#    #+#             */
/*   Updated: 2025/09/10 22:37:49 by patrik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../../include/selector.h"

t_move_simulator	*new_move_simulator(void)
{
	t_move_simulator	*simulator;

	simulator = malloc(sizeof(t_move_simulator));
	if (!simulator)
		return (NULL);
	return (simulator);
}

void	free_move_simulator(t_move_simulator *simulator)
{
	if (simulator)
		free(simulator);
}

static int	simulate_a_to_b_move_stack(t_stack *stack_a, t_stack *stack_b, 
	t_position position, t_stack **new_stack_a, t_stack **new_stack_b)
{
	t_stack	*temp_a;
	t_stack	*temp_b;
	t_node	*node_to_move;
	int		source_index;
	int		target_index;
	int		rotation_cost;

	temp_a = clone_stack(stack_a);
	if (!temp_a)
		return (INT_MAX);
	temp_b = clone_stack(stack_b);
	if (!temp_b)
	{
		free_stack(temp_a);
		return (INT_MAX);
	}
	source_index = normalize_index(get_size(stack_a), position.cost_a);
	target_index = normalize_index(get_size(stack_b), position.cost_b);
	node_to_move = get_node_at_index(temp_a, source_index);
	if (!node_to_move)
	{
		free_stack(temp_a);
		free_stack(temp_b);
		return (INT_MAX);
	}
	remove_node_from_stack(temp_a, node_to_move);
	insert_node_at_index(temp_b, node_to_move, target_index);
	rotation_cost = merged_cost(position.cost_a, position.cost_b);
	*new_stack_a = temp_a;
	*new_stack_b = temp_b;
	return (rotation_cost + 1);
}

static int	simulate_b_to_a_move_stack(t_stack *stack_a, t_stack *stack_b, 
	t_position position, t_stack **new_stack_a, t_stack **new_stack_b)
{
	t_stack	*temp_a;
	t_stack	*temp_b;
	t_node	*node_to_move;
	int		source_index;
	int		target_index;
	int		rotation_cost;

	temp_a = clone_stack(stack_a);
	if (!temp_a)
		return (INT_MAX);
	temp_b = clone_stack(stack_b);
	if (!temp_b)
	{
		free_stack(temp_a);
		return (INT_MAX);
	}
	source_index = normalize_index(get_size(stack_b), position.cost_b);
	target_index = normalize_index(get_size(stack_a), position.cost_a);
	node_to_move = get_node_at_index(temp_b, source_index);
	if (!node_to_move)
	{
		free_stack(temp_a);
		free_stack(temp_b);
		return (INT_MAX);
	}
	remove_node_from_stack(temp_b, node_to_move);
	insert_node_at_index(temp_a, node_to_move, target_index);
	rotation_cost = merged_cost(position.cost_a, position.cost_b);
	*new_stack_a = temp_a;
	*new_stack_b = temp_b;
	return (rotation_cost + 1);
}

int	simulate_move(t_move_simulator *simulator, t_stack *stack_a, 
	t_stack *stack_b, t_position position, t_move_direction direction, 
	t_stack **new_stack_a, t_stack **new_stack_b)
{
	(void)simulator;
	if (direction == MOVE_A_TO_B)
		return (simulate_a_to_b_move_stack(stack_a, stack_b, 
			position, new_stack_a, new_stack_b));
	else
		return (simulate_b_to_a_move_stack(stack_a, stack_b, 
			position, new_stack_a, new_stack_b));
}

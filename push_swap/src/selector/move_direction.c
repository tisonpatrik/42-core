/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_direction.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: patrik <patrik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 21:41:06 by patrik            #+#    #+#             */
/*   Updated: 2025/09/10 22:31:46 by patrik           ###   ########.fr       */
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

static int	simulate_a_to_b_move(int *stack_a, int size_a, int *stack_b, 
	int size_b, t_position position, int **new_stack_a, int **new_stack_b)
{
	int	source_index;
	int	target_index;
	int	element_value;
	int	new_stack_a_size;
	int	new_stack_b_size;
	int	rotation_cost;

	source_index = normalize_index(size_a, position.cost_a);
	target_index = normalize_index(size_b, position.cost_b);
	element_value = stack_a[source_index];
	rotation_cost = merged_cost(position.cost_a, position.cost_b);
	*new_stack_a = remove_element_at(stack_a, size_a, source_index, &new_stack_a_size);
	if (!*new_stack_a)
		return (INT_MAX);
	*new_stack_b = insert_element_at(stack_b, size_b, target_index, element_value, 
		&new_stack_b_size);
	if (!*new_stack_b)
	{
		free(*new_stack_a);
		return (INT_MAX);
	}
	return (rotation_cost + 1);
}

static int	simulate_b_to_a_move(int *stack_a, int size_a, int *stack_b, 
	int size_b, t_position position, int **new_stack_a, int **new_stack_b)
{
	int	source_index;
	int	target_index;
	int	element_value;
	int	new_stack_a_size;
	int	new_stack_b_size;
	int	rotation_cost;

	source_index = normalize_index(size_b, position.cost_b);
	target_index = normalize_index(size_a, position.cost_a);
	element_value = stack_b[source_index];
	rotation_cost = merged_cost(position.cost_a, position.cost_b);
	*new_stack_b = remove_element_at(stack_b, size_b, source_index, &new_stack_b_size);
	if (!*new_stack_b)
		return (INT_MAX);
	*new_stack_a = insert_element_at(stack_a, size_a, target_index, element_value, 
		&new_stack_a_size);
	if (!*new_stack_a)
	{
		free(*new_stack_b);
		return (INT_MAX);
	}
	return (rotation_cost + 1);
}

int	simulate_move(t_move_simulator *simulator, int *stack_a, int size_a, 
	int *stack_b, int size_b, t_position position, t_move_direction direction, 
	int **new_stack_a, int **new_stack_b)
{
	(void)simulator;
	if (direction == MOVE_A_TO_B)
		return (simulate_a_to_b_move(stack_a, size_a, stack_b, size_b, 
			position, new_stack_a, new_stack_b));
	else
		return (simulate_b_to_a_move(stack_a, size_a, stack_b, size_b, 
			position, new_stack_a, new_stack_b));
}

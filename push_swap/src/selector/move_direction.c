/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_direction.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: patrik <patrik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 21:41:06 by patrik            #+#    #+#             */
/*   Updated: 2025/09/10 21:50:32 by patrik           ###   ########.fr       */
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

int	simulate_move(t_move_simulator *simulator, int *a, int size_a, 
	int *b, int size_b, t_position pos, t_move_direction direction, 
	int **new_a, int **new_b)
{
	int	rot;
	int	ia;
	int	ib;
	int	x;
	int	new_a_size;
	int	new_b_size;

	(void)simulator; 
	rot = merged_cost(pos.cost_a, pos.cost_b);
	if (direction == MOVE_A_TO_B)
	{
		ia = normalize_index(size_a, pos.cost_a);
		ib = normalize_index(size_b, pos.cost_b);
		x = a[ia];
		*new_a = remove_element_at(a, size_a, ia, &new_a_size);
		if (!*new_a)
			return (INT_MAX);
		*new_b = insert_element_at(b, size_b, ib, x, &new_b_size);
		if (!*new_b)
		{
			free(*new_a);
			return (INT_MAX);
		}
		return (rot + 1);
	}
	ib = normalize_index(size_b, pos.cost_b);
	ia = normalize_index(size_a, pos.cost_a);
	x = b[ib];
	*new_b = remove_element_at(b, size_b, ib, &new_b_size);
	if (!*new_b)
		return (INT_MAX);
	*new_a = insert_element_at(a, size_a, ia, x, &new_a_size);
	if (!*new_a)
	{
		free(*new_b);
		return (INT_MAX);
	}
	return (rot + 1);
}

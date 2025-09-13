/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   snapshot_arena.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: patrik <patrik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 00:00:00 by patrik            #+#    #+#             */
/*   Updated: 2025/09/13 14:04:17 by patrik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/snapshot_arena.h"
#include <stdbool.h>
#include <stdlib.h>

static int	*snapshot_stack_values(t_stack *stack, int *size)
{
	t_node	*current;
	int		*values;
	int		i;

	*size = get_size(stack);
	if (*size == 0)
		return (NULL);
	values = malloc(*size * sizeof(int));
	if (!values)
		return (NULL);
	
	i = 0;
	current = get_head(stack);
	while (i < *size)
	{
		values[i] = get_content(current);
		current = get_next(current);
		i++;
	}
	return (values);
}

t_snapshot_arena	*create_snapshot_arena(void)
{
	t_snapshot_arena	*arena;

	arena = malloc(sizeof(t_snapshot_arena));
	if (!arena)
		return (NULL);
	
	arena->a_values = NULL;
	arena->b_values = NULL;
	arena->size_a = 0;
	arena->size_b = 0;
	
	return (arena);
}

void	destroy_snapshot_arena(t_snapshot_arena *arena)
{
	if (!arena)
		return ;
	
	clear_snapshots(arena);
	free(arena);
}

bool	take_snapshots(t_snapshot_arena *arena, t_stack *stack_a, t_stack *stack_b)
{
	if (!arena || !stack_a || !stack_b)
		return (false);
	
	// Clear existing snapshots first
	clear_snapshots(arena);
	
	// Take new snapshots
	arena->a_values = snapshot_stack_values(stack_a, &arena->size_a);
	arena->b_values = snapshot_stack_values(stack_b, &arena->size_b);
	
	// Check if snapshots were successful (NULL is OK for empty stacks)
	if (arena->a_values == NULL && arena->size_a > 0)
	{
		clear_snapshots(arena);
		return (false);
	}
	if (arena->b_values == NULL && arena->size_b > 0)
	{
		clear_snapshots(arena);
		return (false);
	}
	
	return (true);
}

void	clear_snapshots(t_snapshot_arena *arena)
{
	if (!arena)
		return ;
	
	if (arena->a_values)
	{
		free(arena->a_values);
		arena->a_values = NULL;
	}
	if (arena->b_values)
	{
		free(arena->b_values);
		arena->b_values = NULL;
	}
	
	arena->size_a = 0;
	arena->size_b = 0;
}




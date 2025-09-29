/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   snapshot_arena.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptison <ptison@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 20:41:58 by ptison            #+#    #+#             */
/*   Updated: 2025/09/29 22:19:50 by ptison           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/snapshot_arena.h"

static void	clear_snapshots(t_snapshot_arena *arena)
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

bool	take_snapshots(t_snapshot_arena *arena, t_stack *stack_a,
		t_stack *stack_b)
{
	if (!arena || !stack_a || !stack_b)
		return (false);
	clear_snapshots(arena);
	arena->a_values = snapshot_stack_values(stack_a, &arena->size_a);
	arena->b_values = snapshot_stack_values(stack_b, &arena->size_b);
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

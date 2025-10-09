/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   separator_arena.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptison <ptison@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 18:49:46 by ptison            #+#    #+#             */
/*   Updated: 2025/10/09 11:34:52 by ptison           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/separator.h"
#include <stdbool.h>
#include <stdlib.h>

void	free_separator_arena(t_separator_arena *arena)
{
	if (!arena)
		return ;
	if (arena->arena)
		ft_arena_destroy(arena->arena);
	free(arena);
}

static size_t	calculate_arena_size(int element_count)
{
	size_t	size;

	size = sizeof(t_separator_arena);
	size += sizeof(t_lis_computation);
	size += sizeof(t_node *) * (size_t)element_count;
	size += sizeof(t_node *) * (size_t)element_count;
	size += sizeof(int) * (size_t)element_count;
	size += sizeof(int) * (size_t)element_count;
	size += sizeof(int) * (size_t)element_count;
	return (size);
}

static void	*setup_arena_memory_layout(t_separator_arena *arena,
		int element_count)
{
	arena->computation = ft_arena_alloc(arena->arena,
			sizeof(t_lis_computation));
	arena->lis_nodes = ft_arena_alloc(arena->arena, sizeof(t_node *)
			* (size_t)element_count);
	arena->computation->nodes = ft_arena_alloc(arena->arena, sizeof(t_node *)
			* (size_t)element_count);
	arena->computation->values = ft_arena_alloc(arena->arena, sizeof(int)
			* (size_t)element_count);
	arena->computation->lis_lengths = ft_arena_alloc(arena->arena, sizeof(int)
			* (size_t)element_count);
	arena->computation->previous_indices = ft_arena_alloc(arena->arena,
			sizeof(int) * (size_t)element_count);
	return (arena);
}

t_separator_arena	*allocate_separator_arena(int element_count)
{
	t_separator_arena	*arena;
	size_t				arena_size;

	if (element_count <= 0)
		return (NULL);
	arena_size = calculate_arena_size(element_count);
	arena = malloc(sizeof(*arena));
	if (!arena)
		return (NULL);
	arena->arena = ft_arena_create(arena_size);
	if (!arena->arena)
	{
		free(arena);
		return (NULL);
	}
	setup_arena_memory_layout(arena, element_count);
	arena->computation->n = element_count;
	arena->lis_length = 0;
	return (arena);
}

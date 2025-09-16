/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_arena.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: patrik <patrik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 18:49:46 by ptison            #+#    #+#             */
/*   Updated: 2025/09/16 21:40:58 by patrik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/separator.h"
#include <stdbool.h>
#include <stdlib.h>

void	free_separator_arena(t_separator_arena *arena)
{
	if (!arena)
		return ;
	if (arena->arena_memory)
		free(arena->arena_memory);
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
	char	*memory;
	size_t	offset;

	memory = (char *)arena->arena_memory;
	offset = sizeof(t_separator_arena);
	arena->computation = (t_lis_computation *)(memory + offset);
	offset += sizeof(t_lis_computation);
	arena->lis_nodes = (t_node **)(memory + offset);
	offset += sizeof(t_node *) * (size_t)element_count;
	arena->computation->nodes = (t_node **)(memory + offset);
	offset += sizeof(t_node *) * (size_t)element_count;
	arena->computation->values = (int *)(memory + offset);
	offset += sizeof(int) * (size_t)element_count;
	arena->computation->lis_lengths = (int *)(memory + offset);
	offset += sizeof(int) * (size_t)element_count;
	arena->computation->previous_indices = (int *)(memory + offset);
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
	arena->arena_memory = malloc(arena_size);
	if (!arena->arena_memory)
	{
		free(arena);
		return (NULL);
	}
	arena->arena_size = arena_size;
	setup_arena_memory_layout(arena, element_count);
	arena->computation->n = element_count;
	return (arena);
}

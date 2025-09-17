/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   selector_arena.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: patrik <patrik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 20:43:24 by ptison            #+#    #+#             */
/*   Updated: 2025/09/17 22:21:59 by patrik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/selector.h"
#include <stdbool.h>
#include <stdlib.h>

void	free_selector_arena(t_selector_arena *arena)
{
	if (!arena)
		return ;
	if (arena->arena_memory)
		free(arena->arena_memory);
	if (arena->snapshot_arena)
		destroy_snapshot_arena(arena->snapshot_arena);
	free(arena);
}

static size_t	calculate_arena_size(int max_candidates, int len_of_inputs)
{
	size_t	size;

	size = sizeof(t_candidate) * (size_t)max_candidates;
	size += sizeof(t_candidate) * (size_t)max_candidates;
	size += sizeof(t_candidate) * (size_t)max_candidates;
	size += sizeof(int) * (size_t)len_of_inputs;
	size += sizeof(int) * (size_t)len_of_inputs;
	return (size);
}

static void	*setup_arena_memory_layout(t_selector_arena *arena,
		int max_candidates, int len_of_inputs)
{
	char	*memory;
	size_t	offset;

	memory = (char *)arena->arena_memory;
	offset = 0;
	arena->candidates = (t_candidate *)(memory + offset);
	offset += sizeof(t_candidate) * (size_t)max_candidates;
	arena->filtered_candidates = (t_candidate *)(memory + offset);
	offset += sizeof(t_candidate) * (size_t)max_candidates;
	arena->top_k_candidates = (t_candidate *)(memory + offset);
	offset += sizeof(t_candidate) * (size_t)max_candidates;
	arena->temp_a_values = (int *)(memory + offset);
	offset += sizeof(int) * (size_t)len_of_inputs;
	arena->temp_b_values = (int *)(memory + offset);
	return (arena);
}

t_selector_arena	*allocate_selector_arena(int max_candidates, int len_of_inputs)
{
	t_selector_arena	*arena;
	size_t				arena_size;

	if (max_candidates <= 0 || len_of_inputs <= 0)
		return (NULL);
	arena_size = calculate_arena_size(max_candidates, len_of_inputs);
	arena = malloc(sizeof(*arena));
	if (!arena)
		return (NULL);
	arena->arena_memory = malloc(arena_size);
	if (!arena->arena_memory)
	{
		free(arena);
		return (NULL);
	}
	arena->snapshot_arena = create_snapshot_arena();
	if (!arena->snapshot_arena)
	{
		free(arena->arena_memory);
		free(arena);
		return (NULL);
	}
	arena->arena_size = arena_size;
	arena->max_candidates = max_candidates;
	arena->candidate_count = 0;
	arena->filtered_count = 0;
	arena->top_k_count = 0;
	setup_arena_memory_layout(arena, max_candidates, len_of_inputs);
	return (arena);
}

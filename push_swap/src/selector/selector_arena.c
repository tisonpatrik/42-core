/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   selector_arena.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: patrik <patrik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 20:43:24 by ptison            #+#    #+#             */
/*   Updated: 2025/09/20 11:15:21 by patrik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/selector.h"
#include <stdbool.h>
#include <stdlib.h>

void	free_selector_arena(t_selector_arena *arena)
{
	if (!arena)
		return ;
	if (arena->arena)
		ft_arena_destroy(arena->arena);
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

static void	initialize_arena_fields(t_selector_arena *arena, int max_candidates)
{
	arena->max_candidates = max_candidates;
	arena->candidate_count = 0;
	arena->filtered_count = 0;
	arena->top_k_count = 0;
}

static void	*setup_arena_memory_layout(t_selector_arena *arena,
		int max_candidates, int len_of_inputs)
{
	arena->candidates = ft_arena_alloc(arena->arena, 
		sizeof(t_candidate) * (size_t)max_candidates);
	arena->filtered_candidates = ft_arena_alloc(arena->arena,
		sizeof(t_candidate) * (size_t)max_candidates);
	arena->top_k_candidates = ft_arena_alloc(arena->arena,
		sizeof(t_candidate) * (size_t)max_candidates);
	arena->temp_a_values = ft_arena_alloc(arena->arena,
		sizeof(int) * (size_t)len_of_inputs);
	arena->temp_b_values = ft_arena_alloc(arena->arena,
		sizeof(int) * (size_t)len_of_inputs);
	return (arena);
}

t_selector_arena	*allocate_arena(int max_candidates,
		int len_of_inputs)
{
	t_selector_arena	*arena;
	size_t				arena_size;

	if (max_candidates <= 0 || len_of_inputs <= 0)
		return (NULL);
	arena_size = calculate_arena_size(max_candidates, len_of_inputs);
	arena = malloc(sizeof(*arena));
	if (!arena)
		return (NULL);
	arena->arena = ft_arena_create(arena_size);
	if (!arena->arena)
	{
		free(arena);
		return (NULL);
	}
	arena->snapshot_arena = create_snapshot_arena();
	if (!arena->snapshot_arena)
	{
		ft_arena_destroy(arena->arena);
		free(arena);
		return (NULL);
	}
	initialize_arena_fields(arena, max_candidates);
	setup_arena_memory_layout(arena, max_candidates, len_of_inputs);
	return (arena);
}

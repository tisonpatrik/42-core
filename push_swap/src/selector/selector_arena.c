/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   selector_arena.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: patrik <patrik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 00:00:00 by patrik            #+#    #+#             */
/*   Updated: 2025/09/12 21:41:00 by patrik           ###   ########.fr       */
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
	free(arena);
}

static size_t	calculate_arena_size(int max_candidates, int max_stack_size)
{
	size_t	size;

	size = sizeof(t_candidate) * (size_t)max_candidates; // For candidates array
	size += sizeof(int) * (size_t)max_stack_size; // For stack A snapshot
	size += sizeof(int) * (size_t)max_stack_size; // For stack B snapshot
	size += sizeof(t_candidate) * (size_t)max_candidates; // For filtered candidates
	size += sizeof(t_candidate) * (size_t)max_candidates; // For top-k candidates
	return (size);
}

static void	*setup_arena_memory_layout(t_selector_arena *arena, int max_candidates, int max_stack_size)
{
	char	*memory;
	size_t	offset;

	memory = (char *)arena->arena_memory;
	offset = 0;
	
	arena->candidates = (t_candidate *)(memory + offset);
	offset += sizeof(t_candidate) * (size_t)max_candidates;
	
	arena->stack_a_snapshot = (int *)(memory + offset);
	offset += sizeof(int) * (size_t)max_stack_size;
	
	arena->stack_b_snapshot = (int *)(memory + offset);
	offset += sizeof(int) * (size_t)max_stack_size;
	
	arena->filtered_candidates = (t_candidate *)(memory + offset);
	offset += sizeof(t_candidate) * (size_t)max_candidates;
	
	arena->top_k_candidates = (t_candidate *)(memory + offset);
	
	return (arena);
}

t_selector_arena	*allocate_selector_arena(int max_candidates, int max_stack_size)
{
	t_selector_arena	*arena;
	size_t			arena_size;

	if (max_candidates <= 0 || max_stack_size <= 0)
		return (NULL);
	arena_size = calculate_arena_size(max_candidates, max_stack_size);
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
	arena->max_candidates = max_candidates;
	arena->max_stack_size = max_stack_size;
	setup_arena_memory_layout(arena, max_candidates, max_stack_size);
	return (arena);
}

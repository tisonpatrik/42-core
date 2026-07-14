/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_arena.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omaly <student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/20 11:45:52 by ptison            #+#    #+#             */
/*   Updated: 2026/02/26 12:07:15 by omaly            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/allocator.h"

t_arena	*ft_arena_create(size_t capacity)
{
	t_arena	*arena;

	if (capacity == 0)
		return (NULL);
	arena = malloc(sizeof(t_arena));
	if (!arena)
		return (NULL);
	arena->base = malloc(capacity);
	if (!arena->base)
	{
		free(arena);
		return (NULL);
	}
	arena->capacity = capacity;
	arena->offset = 0;
	return (arena);
}

void	ft_arena_destroy(t_arena *arena)
{
	if (!arena)
		return ;
	if (arena->base)
		free(arena->base);
	free(arena);
}

void	*ft_arena_push(t_arena *arena, size_t size)
{
	void	*ptr;
	size_t	aligned_size;
	size_t	i;

	if (!arena || size == 0)
		return (NULL);
	aligned_size = (size + 7) & ~7;
	if (arena->offset + aligned_size > arena->capacity)
		return (NULL);
	ptr = arena->base + arena->offset;
	arena->offset += aligned_size;
	i = 0;
	while (i < aligned_size)
	{
		((uint8_t *)ptr)[i] = 0;
		i++;
	}
	return (ptr);
}

void	ft_arena_reset(t_arena *arena)
{
	if (arena)
		arena->offset = 0;
}

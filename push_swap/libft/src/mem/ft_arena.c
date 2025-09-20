/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_arena.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptison <ptison@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/20 11:45:52 by ptison            #+#    #+#             */
/*   Updated: 2025/09/20 11:46:01 by ptison           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/mem.h"
#include <stdlib.h>

t_arena	*ft_arena_create(size_t size)
{
	t_arena	*arena;

	if (size == 0)
		return (NULL);
	arena = malloc(sizeof(t_arena));
	if (!arena)
		return (NULL);
	arena->memory = malloc(size);
	if (!arena->memory)
	{
		free(arena);
		return (NULL);
	}
	arena->size = size;
	arena->offset = 0;
	return (arena);
}

void	ft_arena_destroy(t_arena *arena)
{
	if (!arena)
		return ;
	if (arena->memory)
		free(arena->memory);
	free(arena);
}

void	*ft_arena_alloc(t_arena *arena, size_t size)
{
	void	*ptr;
	size_t	aligned_size;

	if (!arena || size == 0)
		return (NULL);
	aligned_size = (size + 7) & ~7;
	if (arena->offset + aligned_size > arena->size)
		return (NULL);
	ptr = (char *)arena->memory + arena->offset;
	arena->offset += aligned_size;
	return (ptr);
}

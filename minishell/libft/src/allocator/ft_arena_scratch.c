/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_arena_scratch.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omaly <student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/26 11:34:21 by omaly             #+#    #+#             */
/*   Updated: 2026/02/26 11:34:31 by omaly            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/allocator.h"

/*
** Marks the current offset of the arena to be restored later.
** This allows temporary allocations inside a function scope.
*/
t_arena_temp	ft_scratch_begin(t_arena *arena)
{
	t_arena_temp	temp;

	temp.arena = arena;
	if (arena)
		temp.saved_offset = arena->offset;
	else
		temp.saved_offset = 0;
	return (temp);
}

/*
** Restores the arena to the offset saved by ft_scratch_begin.
** Instantly invalidates all allocations made after the begin call.
*/
void	ft_scratch_end(t_arena_temp temp)
{
	if (temp.arena)
		temp.arena->offset = temp.saved_offset;
}

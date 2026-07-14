/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   allocator.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omaly <student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/26 11:34:59 by omaly             #+#    #+#             */
/*   Updated: 2026/02/26 12:07:24 by omaly            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ALLOCATOR_H
# define ALLOCATOR_H

# include <stddef.h>
# include <stdint.h>
# include <stdlib.h>

typedef struct s_arena
{
	uint8_t		*base;
	size_t		offset;
	size_t		capacity;
}				t_arena;

typedef struct s_arena_temp
{
	t_arena		*arena;
	size_t		saved_offset;
}				t_arena_temp;

t_arena			*ft_arena_create(size_t capacity);
void			ft_arena_destroy(t_arena *arena);
void			*ft_arena_push(t_arena *arena, size_t size);
void			ft_arena_reset(t_arena *arena);

t_arena_temp	ft_scratch_begin(t_arena *arena);
void			ft_scratch_end(t_arena_temp temp);

#endif

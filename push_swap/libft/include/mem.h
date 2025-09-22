/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mem.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptison <ptison@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/25 13:28:28 by ptison            #+#    #+#             */
/*   Updated: 2025/09/22 22:16:22 by ptison           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MEM_H
# define MEM_H

# include <stddef.h>

typedef struct s_arena
{
	void	*memory;
	size_t	size;
	size_t	offset;
}			t_arena;

void		*ft_bzero(void *s, size_t n);
void		*ft_memchr(const void *s, int c, size_t n);
int			ft_memcmp(const void *s1, const void *s2, size_t n);
void		*ft_memcpy(void *dst, const void *src, size_t n);
void		*ft_memmove(void *dst, const void *src, size_t len);
void		*ft_memset(void *b, int c, size_t len);
void		*ft_calloc(size_t nelem, size_t elsize);
void		ft_free_array(char **array);
void		ft_swap_int(int *a, int *b);

t_arena		*ft_arena_create(size_t size);
void		ft_arena_destroy(t_arena *arena);
void		*ft_arena_alloc(t_arena *arena, size_t size);

void		*ft_realloc(void *ptr, size_t old_size, size_t new_size);

#endif

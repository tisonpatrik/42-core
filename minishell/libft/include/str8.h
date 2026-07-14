/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str8.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omaly <student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/26 12:04:27 by omaly             #+#    #+#             */
/*   Updated: 2026/02/26 12:05:22 by omaly            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STR8_H
# define STR8_H

# include "allocator.h"
# include "core.h"
# include "mem.h"
# include "str.h"
# include <stdbool.h>

typedef struct s_str8
{
	uint8_t				*str;
	size_t				len;
}						t_str8;

typedef struct s_str8_node
{
	t_str8				string;
	struct s_str8_node	*next;
}						t_str8_node;

typedef struct s_str8_list
{
	t_str8_node			*first;
	t_str8_node			*last;
	size_t				total_size;
}						t_str8_list;

/* Constructors & Creators */
t_str8					ft_str8_from_cstr(const char *cstr);
t_str8					ft_str8_create(uint8_t *str, size_t len);
t_str8					ft_str8_substr(t_str8 s, size_t start, size_t len);

/* Utils */
bool					ft_str8_match(t_str8 a, t_str8 b);
int						ft_str8_cmp(t_str8 a, t_str8 b);
bool					ft_is_valid_identifier(t_str8 key);

/* Conversion & Allocation */
char					*str8_to_cstr(t_arena *arena, t_str8 s);
t_str8					ft_str8_join(t_arena *arena, t_str8 s1, t_str8 s2);
t_str8					ft_str8_dup(t_arena *arena, t_str8 s);
#endif

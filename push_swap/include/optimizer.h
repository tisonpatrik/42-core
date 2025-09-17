/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   optimizer.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: patrik <patrik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 21:11:57 by ptison            #+#    #+#             */
/*   Updated: 2025/09/17 22:54:21 by patrik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OPTIMIZER_H
# define OPTIMIZER_H

# include "../libft/include/libft.h"
# include "ops.h"
# include <stdlib.h>

typedef struct s_optimizer_arena
{
	t_operation	*operations;
	size_t		capacity;
	size_t		used;
	void		*arena_memory;
	size_t		arena_size;
}				t_optimizer_arena;

t_optimizer_arena	*create_optimizer_arena(size_t capacity);
void				destroy_optimizer_arena(t_optimizer_arena *arena);
t_operation			*arena_alloc_operation(t_optimizer_arena *arena);
void				reset_optimizer_arena(t_optimizer_arena *arena);

void		optimize_ops(t_list **seq);

t_list		*bubble_across_other_stack(t_list *src, int max_gap, bool *changed);
bool		is_pure_a(t_operation op);
bool		is_pure_b(t_operation op);

t_list		*merge_neighbors(t_list *src, bool *changed);

t_list		*cancel_inverse_pairs(t_list *src, bool *changed);
bool		is_inverse(t_operation a, t_operation b);
t_list		*cancel_across_other_stack_a(t_list *src, bool *changed);
t_list		*cancel_across_other_stack_b(t_list *src, bool *changed);

bool		touches_a(t_operation op);
bool		touches_b(t_operation op);
bool		is_barrier(t_operation op);

void		list_swap_nodes(t_list *list, int i, int j);
t_list		*list_remove_at(t_list *list, int index);
t_list		*list_insert_at(t_list *list, t_operation op, int index);
t_operation	get_operation_at_index(t_list *list, int index);
void		set_operation_at_index(t_list *list, int index, t_operation op);
bool		bubble_operation(t_list *out, int i, int j, bool is_a);

#endif

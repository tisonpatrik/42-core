/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   optimizer.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: patrik <patrik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/19 22:42:52 by ptison            #+#    #+#             */
/*   Updated: 2025/09/19 23:13:59 by patrik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OPTIMIZER_H
# define OPTIMIZER_H

# include "../libft/include/libft.h"
# include "ops.h"
# include <stdbool.h>
# include <stdlib.h>

typedef struct s_merge_context
{
	t_operation		a;
	t_operation		b;
	t_list			**dst;
	t_list			**current;
}					t_merge_context;

typedef struct s_bubble_context
{
	t_list			*out;
	int				i;
	int				n;
	int				max_gap;
	bool			*changed;
	bool			is_a;
}					t_bubble_context;

typedef struct s_cancel_context
{
	t_operation		op;
	t_list			*current;
	t_list			**dst;
	bool			*has_changed;
	t_list			**current_ptr;
}					t_cancel_context;

typedef struct s_optimizer_config
{
	int				max_bubble_gap;
	int				max_iterations;
}					t_optimizer_config;

void				*copy_operation(void *content);
void				add_operation_to_list(t_list **dst, t_operation op);
void				replace_sequence_if_changed(t_list **seq, t_list *new_seq,
						bool changed, bool *overall_changed);

t_operation			get_operation_at_index(t_list *list, int index);

t_list				*bubble_next_stack(t_list *src, bool *changed);
bool				is_pure_a(t_operation op);
bool				is_pure_b(t_operation op);

t_list				*merge_neighbors(t_list *src, bool *changed);
t_operation			get_absorption_rr_rra(t_operation a);
t_operation			get_absorption_rr_rrb(t_operation a);
t_operation			get_absorption_rrr_ra(t_operation a);
t_operation			get_absorption_rrr_rb(t_operation a);

bool				try_merge_rotate_pairs(t_merge_context *ctx);
bool				try_merge_swap_pairs(t_merge_context *ctx);
bool				try_merge_absorption_cases(t_merge_context *ctx);

t_list				*cancel_inverse_pairs(t_list *src, bool *changed);

t_list				*cancel_across_other_stack_a(t_list *src, bool *changed);
t_list				*cancel_across_other_stack_b(t_list *src, bool *changed);

bool				search_for_inverse_a(t_operation op, t_list *current,
						t_list **dst, bool *has_changed);
bool				search_for_inverse_b(t_operation op, t_list *current,
						t_list **dst, bool *has_changed);
void				process_operation_a(t_cancel_context *ctx);

bool				touches_a(t_operation op);
bool				touches_b(t_operation op);
bool				is_barrier(t_operation op);

t_operation			get_operation_at_index(t_list *list, int index);
bool				bubble_operation(t_list *out, int i, int j, bool is_a);
void				process_operation_at_index(t_bubble_context *ctx);

void				optimize_ops(t_list **seq);

#endif

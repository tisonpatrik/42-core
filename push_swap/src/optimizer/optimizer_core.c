/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   optimizer_core.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: patrik <patrik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/19 20:49:14 by ptison            #+#    #+#             */
/*   Updated: 2025/09/22 11:35:35 by patrik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/optimizer.h"

static void	apply_optimization_pass(t_list **seq, bool *changed)
{
	bool	change;
	t_list	*new_seq;

	new_seq = bubble_next_stack(*seq, &change);
	replace_sequence_if_changed(seq, new_seq, change, changed);
	new_seq = merge_neighbors(*seq, &change);
	replace_sequence_if_changed(seq, new_seq, change, changed);
	new_seq = cancel_inverse_pairs(*seq, &change);
	replace_sequence_if_changed(seq, new_seq, change, changed);
	new_seq = cancel_across_other_stack_a(*seq, &change);
	replace_sequence_if_changed(seq, new_seq, change, changed);
	new_seq = cancel_across_other_stack_b(*seq, &change);
	replace_sequence_if_changed(seq, new_seq, change, changed);
}

static void	run_optimization_loop(t_list **seq)
{
	bool	changed;

	changed = true;
	while (changed)
	{
		changed = false;
		apply_optimization_pass(seq, &changed);
	}
}

static bool	validate_operation_sequence(t_list *seq)
{
	if (!seq)
		return (false);
	if (ft_lstsize(seq) < 2)
		return (false);
	return (true);
}

void	optimize_ops(t_list **seq)
{
	if (!validate_operation_sequence(*seq))
		return ;
	run_optimization_loop(seq);
}

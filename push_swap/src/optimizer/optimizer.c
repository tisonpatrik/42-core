/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   optimizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: patrik <patrik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 21:37:30 by patrik            #+#    #+#             */
/*   Updated: 2025/09/17 23:09:47 by patrik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/optimizer.h"


void	apply_optimization_pass(t_list **seq, bool *changed)
{
	bool change;
	t_list *new_seq;
	
	// Bubble operations
	new_seq = bubble_across_other_stack(*seq, 4, &change);
	replace_sequence_if_changed(seq, new_seq, change, changed);
	
	// Merge neighbors
	new_seq = merge_neighbors(*seq, &change);
	replace_sequence_if_changed(seq, new_seq, change, changed);
	
	// Cancel inverse pairs
	new_seq = cancel_inverse_pairs(*seq, &change);
	replace_sequence_if_changed(seq, new_seq, change, changed);
	
	// Cancel across other stack A
	new_seq = cancel_across_other_stack_a(*seq, &change);
	replace_sequence_if_changed(seq, new_seq, change, changed);
	
	// Cancel across other stack B
	new_seq = cancel_across_other_stack_b(*seq, &change);
	replace_sequence_if_changed(seq, new_seq, change, changed);
}

void	run_optimization_loop(t_list **seq)
{
	bool changed = true;
	
	while (changed)
	{
		changed = false;
		apply_optimization_pass(seq, &changed);
	}
}

void	optimize_ops(t_list **seq)
{
	if (!validate_operation_sequence(*seq))
		return;
	
	run_optimization_loop(seq);
}

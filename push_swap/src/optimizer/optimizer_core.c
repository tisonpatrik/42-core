
#include "../../include/optimizer.h"

void	apply_optimization_pass(t_list **seq, bool *changed)
{
	bool change;
	t_list *new_seq;
	
	new_seq = bubble_across_other_stack(*seq, 4, &change);
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

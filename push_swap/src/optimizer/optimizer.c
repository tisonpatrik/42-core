#include "../../include/optimizer.h"

void optimize_ops(t_list **seq)
{
	if (!seq || !*seq)
		return;
	
	int len = ft_lstsize(*seq);
	if (len < 2)
		return;
	
	const int max_bubble = 4;
	bool changed = true;
	
	while (changed)
	{
		changed = false;
		bool c;
		
		// Apply optimizations similar to Go version
		t_list *new_seq = bubble_across_other_stack(*seq, max_bubble, &c);
		if (c)
		{
			ft_lstclear(seq, free);
			*seq = new_seq;
			changed = true;
		}
		else
		{
			ft_lstclear(&new_seq, free); // Free the copy since no changes were made
		}
		
		new_seq = merge_neighbors(*seq, &c);
		if (c)
		{
			ft_lstclear(seq, free);
			*seq = new_seq;
			changed = true;
		}
		else
		{
			ft_lstclear(&new_seq, free); // Free the copy since no changes were made
		}
		
		new_seq = cancel_inverse_pairs(*seq, &c);
		if (c)
		{
			ft_lstclear(seq, free);
			*seq = new_seq;
			changed = true;
		}
		else
		{
			ft_lstclear(&new_seq, free); // Free the copy since no changes were made
		}
		
		new_seq = cancel_across_other_stack_a(*seq, &c);
		if (c)
		{
			ft_lstclear(seq, free);
			*seq = new_seq;
			changed = true;
		}
		else
		{
			ft_lstclear(&new_seq, free); // Free the copy since no changes were made
		}
		
		new_seq = cancel_across_other_stack_b(*seq, &c);
		if (c)
		{
			ft_lstclear(seq, free);
			*seq = new_seq;
			changed = true;
		}
		else
		{
			ft_lstclear(&new_seq, free); // Free the copy since no changes were made
		}
	}
}

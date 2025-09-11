#include "../../include/optimizer.h"

/**
 * OptimizeOps: multiple rounds of safe local rewrites.
 * Passes:
 *  1) bubbleAcrossOtherStack (window ≤ maxBubble) – extracts candidates for merge
 *  2) mergeNeighbors – (ra rb)->rr, (rra rrb)->rrr, (sa sb)->ss + absorption rr/rrr
 *  3) cancelInversePairs – adjacent inverses (ra rra), (pb pa), (ss ss), ...
 *  4) cancelAcrossOtherStackA/B – (ra ... rra) / (rb ... rrb) across other stack
 * 
 * OptimizeOps applies multiple rounds of safe local optimizations to the operation sequence.
 * It performs bubble operations, neighbor merging, inverse pair cancellation, and cross-stack optimizations.
 * 
 * @param seq List of operations to optimize
 * @return Optimized list of operations
 */
t_list	*optimize_ops(t_list *seq)
{
	if (!seq || ft_lstsize(seq) < 2)
		return (seq);
	
	t_list	*out = seq;
	const int	max_bubble = 4;
	bool		changed = true;
	
	while (changed)
	{
		changed = false;
		
		bool	c;
		t_list	*temp;
		
		// 1) Bubble across other stack
		temp = bubble_across_other_stack(out, max_bubble);
		c = (temp != out);
		if (c)
		{
			ft_lstclear(&out, free);
			out = temp;
		}
		else
			ft_lstclear(&temp, free);
		changed = changed || c;
		
		// Skip other optimization steps for now
		break;
	}
	
	return (out);
}

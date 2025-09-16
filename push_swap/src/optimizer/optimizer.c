/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   optimizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: patrik <patrik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 21:37:30 by patrik            #+#    #+#             */
/*   Updated: 2025/09/16 21:40:58 by patrik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
		
		t_list *new_seq = bubble_across_other_stack(*seq, max_bubble, &c);
		if (c)
		{
			ft_lstclear(seq, free);
			*seq = new_seq;
			changed = true;
		}
		else
		{
			ft_lstclear(&new_seq, free);
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
			ft_lstclear(&new_seq, free);
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
			ft_lstclear(&new_seq, free);
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
			ft_lstclear(&new_seq, free);
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
			ft_lstclear(&new_seq, free);
		}
	}
}

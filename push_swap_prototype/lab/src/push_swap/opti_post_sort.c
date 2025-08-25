/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   opti_post_sort.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: patrik <patrik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 20:58:19 by ugerkens          #+#    #+#             */
/*   Updated: 2025/08/25 12:48:19 by patrik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/push_swap.h"

void	post_sort_optimization(t_ps *data)
{
	// Debug: Log function entry
	
	if (!data->op_list)
	{
		return ;
	}
	
	eliminate_neutral_op(data->op_list);
	
	merge_op(data->op_list);
	
}

void	eliminate_neutral_op(t_list *op_list)
{
	t_list	*ref;
	t_list	*cmp;
	t_op	op_neutral;

	// Debug: Log function entry
	
	ref = op_list->next;
	
	while (ref && ref->next)
	{
		
		op_neutral = neutral_op(op_from(ref));
		
		
		if (op_neutral)
		{
			
			cmp = ref->next;
			
			
			while (!op_on_same_stack(op_from(ref), op_from(cmp))
				&& op_from(cmp) != op_neutral && cmp->next)
			{
				
				cmp = cmp->next;
			}
			
			
			
			if (ref->prev && op_from(cmp) == op_neutral)
			{
				
				ref = ref->prev;
				remove_op(ref->next);
				remove_op(cmp);
				continue ;
			}
		}
		ref = ref->next;
	}
	
	
}

void	merge_op(t_list *op_list)
{
	t_list	*reader;
	t_op	child;

	// Debug: Log function entry
	
	
	reader = op_list;
	
	
	while (reader && reader->next)
	{
		
		
		child = child_op(op_from(reader), op_from(reader->next));
		
		
		if (child)
		{
			
			remove_op(reader->next);
			reader->content = (void *)(uintptr_t)child;
		}
		else
		{
			
		}
		
		reader = reader->next;
	}
	
	
}

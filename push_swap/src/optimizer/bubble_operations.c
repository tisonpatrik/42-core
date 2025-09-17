/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bubble_operations.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: patrik <patrik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 21:37:14 by patrik            #+#    #+#             */
/*   Updated: 2025/09/17 23:04:02 by patrik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/optimizer.h"


t_operation	get_operation_at_index(t_list *list, int index)
{
	t_list	*current = list;
	int		i = 0;
	
	while (current != NULL && i < index)
	{
		current = current->next;
		i++;
	}
	
	if (current == NULL)
		return (SA);
	return (*(t_operation*)current->content);
}


void	set_operation_at_index(t_list *list, int index, t_operation op)
{
	t_list	*current = list;
	int		i = 0;
	
	while (current != NULL && i < index)
	{
		current = current->next;
		i++;
	}
	
	if (current != NULL)
		*(t_operation*)current->content = op;
}


bool	bubble_operation(t_list *out, int i, int j, bool is_a)
{
	for (int k = i + 1; k < j; k++)
	{
		t_operation op_k = get_operation_at_index(out, k);
		if (is_barrier(op_k))
			return (false);
		if (is_a && (touches_a(op_k) || (!touches_b(op_k) && !is_pure_b(op_k))))
			return (false);
		if (!is_a && (touches_b(op_k) || (!touches_a(op_k) && !is_pure_a(op_k))))
			return (false);
	}
	for (int k = j; k > i + 1; k--)
	{
		t_operation temp = get_operation_at_index(out, k);
		set_operation_at_index(out, k, get_operation_at_index(out, k - 1));
		set_operation_at_index(out, k - 1, temp);
	}
	return (true);
}


t_list	*bubble_across_other_stack(t_list *src, int max_gap, bool *changed)
{
	int		n = ft_lstsize(src);
	if (n < 3)
	{
		*changed = false;
		return (src);
	}
	
	t_list	*out = ft_lstmap(src, copy_operation, free);
	if (out == NULL)
		return (NULL);
	*changed = false;
	
	for (int i = 0; i < n - 1; i++)
	{
		t_operation a = get_operation_at_index(out, i);
		
		if (a == RA || a == RRA)
		{
			t_operation want = RB;
			if (a == RRA)
				want = RRB;
			for (int j = i + 1; j < n && j - i - 1 <= max_gap; j++)
			{
				t_operation op_j = get_operation_at_index(out, j);
				if (op_j == want)
				{
					if (bubble_operation(out, i, j, true))
					{
						*changed = true;
					}
					break;
				}
				if (is_barrier(op_j) || touches_a(op_j))
					break;
			}
			continue;
		}
		
		if (a == RB || a == RRB)
		{
			t_operation want = RA;
			if (a == RRB)
				want = RRA;
			for (int j = i + 1; j < n && j - i - 1 <= max_gap; j++)
			{
				t_operation op_j = get_operation_at_index(out, j);
				if (op_j == want)
				{
					if (bubble_operation(out, i, j, false))
					{
						*changed = true;
					}
					break;
				}
				if (is_barrier(op_j) || touches_b(op_j))
					break;
			}
			continue;
		}
	}
	
	return (out);
}

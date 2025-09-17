/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cancel_operations.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: patrik <patrik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 21:37:44 by patrik            #+#    #+#             */
/*   Updated: 2025/09/17 23:04:02 by patrik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/optimizer.h"


static void	copy_operations_to_list(t_list **dst, t_list *src_start, t_list *src_end, 
									t_optimizer_arena *arena)
{
	t_list *current = src_start;
	while (current != src_end)
	{
		t_operation *op_ptr = arena_alloc_operation(arena);
		if (op_ptr)
		{
			*op_ptr = *(t_operation*)current->content;
			add_operation_to_list(dst, *op_ptr);
		}
		current = current->next;
	}
}


bool	is_inverse(t_operation a, t_operation b)
{
	switch (a)
	{
		case RA:
			return (b == RRA);
		case RRA:
			return (b == RA);
		case RB:
			return (b == RRB);
		case RRB:
			return (b == RB);
		case RR:
			return (b == RRR);
		case RRR:
			return (b == RR);
		case SA:
			return (b == SA);
		case SB:
			return (b == SB);
		case SS:
			return (b == SS);
		case PA:
			return (b == PB);
		case PB:
			return (b == PA);
		default:
			return (false);
	}
}


t_list	*cancel_inverse_pairs(t_list *src, bool *changed)
{
	if (!src || ft_lstsize(src) < 2)
	{
		if (changed)
			*changed = false;
		return (ft_lstmap(src, copy_operation, free));
	}
	
	t_optimizer_arena *arena = create_optimizer_arena(ft_lstsize(src));
	if (!arena)
	{
		if (changed)
			*changed = false;
		return (NULL);
	}
	
	t_list	*dst = NULL;
	t_list	*current = src;
	bool	has_changed = false;
	
	while (current != NULL)
	{
		if (current->next != NULL && 
			is_inverse(*(t_operation*)current->content, 
					  *(t_operation*)current->next->content))
		{
			has_changed = true;
			current = current->next->next;
		}
		else
		{
			add_operation_to_list(&dst, *(t_operation*)current->content);
			current = current->next;
		}
	}
	
	if (changed)
		*changed = has_changed;
	
	destroy_optimizer_arena(arena);
	return (dst);
}


t_list	*cancel_across_other_stack_a(t_list *src, bool *changed)
{
	if (!src || ft_lstsize(src) < 3)
	{
		if (changed)
			*changed = false;
		return (ft_lstmap(src, copy_operation, free));
	}
	
	t_optimizer_arena *arena = create_optimizer_arena(ft_lstsize(src));
	if (!arena)
	{
		if (changed)
			*changed = false;
		return (NULL);
	}
	
	t_list	*dst = NULL;
	t_list	*current = src;
	bool	has_changed = false;
	
	while (current != NULL)
	{
		t_operation op = *(t_operation*)current->content;
		if (op == RA || op == RRA)
		{
			t_operation inv = (op == RA) ? RRA : RA;
			t_list	*search = current->next;
			
			while (search != NULL)
			{
				if (is_barrier(*(t_operation*)search->content) ||
					touches_a(*(t_operation*)search->content))
					break;
				if (*(t_operation*)search->content == inv)
				{
					has_changed = true;
					copy_operations_to_list(&dst, current->next, search, arena);
					current = search;
					goto next;
				}
				search = search->next;
			}
		}
		add_operation_to_list(&dst, op);
	next:
		current = current->next;
	}
	
	if (changed)
		*changed = has_changed;
	
	destroy_optimizer_arena(arena);
	return (dst);
}


t_list	*cancel_across_other_stack_b(t_list *src, bool *changed)
{
	if (!src || ft_lstsize(src) < 3)
	{
		if (changed)
			*changed = false;
		return (ft_lstmap(src, copy_operation, free));
	}
	
	t_optimizer_arena *arena = create_optimizer_arena(ft_lstsize(src));
	if (!arena)
	{
		if (changed)
			*changed = false;
		return (NULL);
	}
	
	t_list	*dst = NULL;
	t_list	*current = src;
	bool	has_changed = false;
	
	while (current != NULL)
	{
		t_operation op = *(t_operation*)current->content;
		if (op == RB || op == RRB)
		{
			t_operation inv = (op == RB) ? RRB : RB;
			t_list	*search = current->next;
			
			while (search != NULL)
			{
				if (is_barrier(*(t_operation*)search->content) ||
					touches_b(*(t_operation*)search->content))
					break;
				if (*(t_operation*)search->content == inv)
				{
					has_changed = true;
					copy_operations_to_list(&dst, current->next, search, arena);
					current = search;
					goto next;
				}
				search = search->next;
			}
		}
		add_operation_to_list(&dst, op);
	next:
		current = current->next;
	}
	
	if (changed)
		*changed = has_changed;
	
	destroy_optimizer_arena(arena);
	return (dst);
}

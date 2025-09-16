/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cancel_operations.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: patrik <patrik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 21:37:44 by patrik            #+#    #+#             */
/*   Updated: 2025/09/16 21:40:58 by patrik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/optimizer.h"


static void	*copy_operation(void *content)
{
	t_operation *op = malloc(sizeof(t_operation));
	if (op)
		*op = *(t_operation*)content;
	return (op);
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
			t_operation *op = malloc(sizeof(t_operation));
			if (op == NULL)
			{
				ft_lstclear(&dst, free);
				return (NULL);
			}
			*op = *(t_operation*)current->content;
			ft_lstadd_back(&dst, ft_lstnew(op));
			current = current->next;
		}
	}
	
	if (changed)
		*changed = has_changed;
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
					t_list	*temp = current->next;
					while (temp != search)
					{
						t_operation *op_copy = malloc(sizeof(t_operation));
						if (op_copy == NULL)
						{
							ft_lstclear(&dst, free);
							return (NULL);
						}
						*op_copy = *(t_operation*)temp->content;
						ft_lstadd_back(&dst, ft_lstnew(op_copy));
						temp = temp->next;
					}
					current = search;
					goto next;
				}
				search = search->next;
			}
		}
		t_operation *op_copy = malloc(sizeof(t_operation));
		if (op_copy == NULL)
		{
			ft_lstclear(&dst, free);
			return (NULL);
		}
		*op_copy = op;
		ft_lstadd_back(&dst, ft_lstnew(op_copy));
	next:
		current = current->next;
	}
	
	if (changed)
		*changed = has_changed;
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
					// Add A-only operations between them
					has_changed = true;
					t_list	*temp = current->next;
					while (temp != search)
					{
						t_operation *op_copy = malloc(sizeof(t_operation));
						if (op_copy == NULL)
						{
							ft_lstclear(&dst, free);
							return (NULL);
						}
						*op_copy = *(t_operation*)temp->content;
						ft_lstadd_back(&dst, ft_lstnew(op_copy));
						temp = temp->next;
					}
					current = search;
					goto next;
				}
				search = search->next;
			}
		}
		// Add current operation
		t_operation *op_copy = malloc(sizeof(t_operation));
		if (op_copy == NULL)
		{
			ft_lstclear(&dst, free);
			return (NULL);
		}
		*op_copy = op;
		ft_lstadd_back(&dst, ft_lstnew(op_copy));
	next:
		current = current->next;
	}
	
	if (changed)
		*changed = has_changed;
	return (dst);
}

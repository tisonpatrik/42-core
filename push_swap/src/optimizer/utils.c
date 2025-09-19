/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: patrik <patrik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/19 20:48:29 by ptison            #+#    #+#             */
/*   Updated: 2025/09/19 21:58:46 by patrik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/optimizer.h"

void	*copy_operation(void *content)
{
	t_operation	*op;

	op = malloc(sizeof(t_operation));
	if (op)
		*op = *(t_operation *)content;
	return (op);
}

void	add_operation_to_list(t_list **dst, t_operation op)
{
	t_operation	*op_ptr;

	op_ptr = malloc(sizeof(t_operation));
	if (op_ptr)
	{
		*op_ptr = op;
		ft_lstadd_back(dst, ft_lstnew(op_ptr));
	}
}

t_operation	get_operation_at_index(t_list *list, int index)
{
	t_list	*current;
	int		i;

	current = list;
	i = 0;
	while (current != NULL && i < index)
	{
		current = current->next;
		i++;
	}
	if (current == NULL)
		return (SA);
	return (*(t_operation *)current->content);
}



void	replace_sequence_if_changed(t_list **seq, t_list *new_seq, bool changed,
		bool *overall_changed)
{
	if (changed)
	{
		ft_lstclear(seq, free);
		*seq = new_seq;
		*overall_changed = true;
	}
	else
	{
		ft_lstclear(&new_seq, free);
	}
}

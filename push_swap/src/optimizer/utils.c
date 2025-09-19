/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptison <ptison@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/19 20:48:29 by ptison            #+#    #+#             */
/*   Updated: 2025/09/19 20:48:32 by ptison           ###   ########.fr       */
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

t_list	*copy_operation_list(t_list *src)
{
	if (!src)
		return (NULL);
	return (ft_lstmap(src, copy_operation, free));
}

bool	validate_operation_sequence(t_list *seq)
{
	if (!seq)
		return (false);
	if (ft_lstsize(seq) < 2)
		return (false);
	return (true);
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

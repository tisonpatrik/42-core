/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptison <ptison@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 18:46:09 by ptison            #+#    #+#             */
/*   Updated: 2025/09/29 22:24:37 by ptison           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/stack.h"

t_stack	*create_stack(void)
{
	t_stack	*stack;

	stack = (t_stack *)malloc(sizeof(t_stack));
	if (!stack)
		return (NULL);
	stack->head = NULL;
	stack->tail = NULL;
	stack->size = 0;
	return (stack);
}

int	get_size(t_stack *stack)
{
	if (!stack)
		return (0);
	return (stack->size);
}

t_node	*get_head(t_stack *stack)
{
	if (!stack)
		return (NULL);
	return (stack->head);
}

t_node	*get_tail(t_stack *stack)
{
	if (!stack)
		return (NULL);
	return (stack->tail);
}

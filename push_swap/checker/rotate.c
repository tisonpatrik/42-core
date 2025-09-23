/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptison <ptison@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 18:58:29 by ptison            #+#    #+#             */
/*   Updated: 2025/09/23 18:35:43 by ptison           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include <unistd.h>
#include "../include/stack.h"

bool	rotate(t_stack **stack)
{
	t_node	*top_node;
	t_node	*tail_node;

	if (!stack || !*stack)
		return (false);
	if (get_size(*stack) <= 1)
		return (false);
	top_node = get_head(*stack);
	tail_node = get_tail(*stack);
	(*stack)->head = get_next(top_node);
	(*stack)->head->prev = NULL;
	top_node->next = NULL;
	top_node->prev = tail_node;
	tail_node->next = top_node;
	(*stack)->tail = top_node;
	return (true);
}


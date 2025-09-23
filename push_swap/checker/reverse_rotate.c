/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reverse_rotate.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptison <ptison@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 18:51:56 by ptison            #+#    #+#             */
/*   Updated: 2025/09/23 18:35:48 by ptison           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include <unistd.h>
#include "../include/stack.h"

bool	reverse_rotate(t_stack **stack)
{
	t_node	*bottom_node;
	t_node	*head_node;
	t_node	*prev_tail;

	if (!stack || !*stack)
		return (false);
	if (get_size(*stack) <= 1)
		return (false);
	bottom_node = get_tail(*stack);
	head_node = get_head(*stack);
	prev_tail = get_prev(bottom_node);
	(*stack)->tail = prev_tail;
	prev_tail->next = NULL;
	bottom_node->prev = NULL;
	bottom_node->next = head_node;
	head_node->prev = bottom_node;
	(*stack)->head = bottom_node;
	return (true);
}



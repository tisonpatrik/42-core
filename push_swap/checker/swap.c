/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   swap.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptison <ptison@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 18:57:23 by ptison            #+#    #+#             */
/*   Updated: 2025/09/23 18:39:01 by ptison           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include <unistd.h>
#include "../include/stack.h"

bool	swap(t_stack **stack)
{
	int		temp_content;
	t_node	*first_node;
	t_node	*second_node;

	if (!stack || !*stack)
		return (false);
	if (get_size(*stack) < 2)
		return (false);
	first_node = get_head(*stack);
	second_node = get_next(first_node);
	temp_content = get_content(first_node);
	first_node->content = get_content(second_node);
	second_node->content = temp_content;
	return (true);
}
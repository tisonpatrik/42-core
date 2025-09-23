/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptison <ptison@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/17 10:21:27 by ptison            #+#    #+#             */
/*   Updated: 2025/09/23 18:36:13 by ptison           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include <unistd.h>
#include "../include/stack.h"

bool	push(t_stack **source, t_stack **target)
{
	t_node	*popped_node;

	if (!source || !*source)
		return (false);
	if (!target || !*target)
		return (false);
	if (get_size(*source) == 0)
		return (false);
	popped_node = pop(source);
	if (!popped_node)
		return (false);
	push_to_stack(*target, popped_node);
	return (true);
}


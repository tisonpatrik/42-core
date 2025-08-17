/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: patrik <patrik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/17 10:21:27 by ptison            #+#    #+#             */
/*   Updated: 2025/08/17 13:57:13 by patrik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/push_swap.h"
#include <unistd.h>

void	push(t_list **source, t_list **target)
{
	t_list	*node;

	if (!source || !*source)
		return ;
	node = *source;
	*source = node->next;
	node->next = *target;
	*target = node;
}


void push_a(t_list **a, t_list **b)
{
    push(b, a);
    ft_printf("pa\n");
}

void push_b(t_list **a, t_list **b)
{
    push(a, b);
    ft_printf("pb\n");
}

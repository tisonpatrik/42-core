/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reverse_rotate.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: patrik <patrik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/17 10:22:53 by ptison            #+#    #+#             */
/*   Updated: 2025/08/17 13:57:04 by patrik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/push_swap.h"
#include <unistd.h>

void	reverse_rotate(t_list **stack)
{
	t_list	*prev;
	t_list	*last;

	if (!stack || !*stack || !(*stack)->next)
		return ;
	prev = NULL;
	last = *stack;
	while (last->next)
	{
		prev = last;
		last = last->next;
	}
	prev->next = NULL;
	last->next = *stack;
	*stack = last;
}

void reverse_rotate_a(t_list **stack)
{
	reverse_rotate(stack);
	ft_printf("rra\n");
}

void reverse_rotate_b(t_list **stack)
{
	reverse_rotate(stack);
	ft_printf("rrb\n");
}

void reverse_rotate_ab(t_list **a, t_list **b)
{
    reverse_rotate_a(a);
	reverse_rotate_b(b);
    ft_printf("rrr\n");
}

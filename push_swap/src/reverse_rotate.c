/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reverse_rotate.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptison <ptison@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/17 10:22:53 by ptison            #+#    #+#             */
/*   Updated: 2025/08/17 11:17:20 by ptison           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
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
	write(1, "rra\n", 3);
}

void reverse_rotate_b(t_list **stack)
{
	reverse_rotate(stack);
	write(1, "rrb\n", 3);
}

void reverse_rotate_ab(t_list **a, t_list **b)
{
    reverse_rotate_a(a);
	reverse_rotate_b(b);
    write(1, "rrr\n", 4);
}

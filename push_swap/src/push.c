/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptison <ptison@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/17 10:21:27 by ptison            #+#    #+#             */
/*   Updated: 2025/08/17 10:33:36 by ptison           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
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
    write(1, "pa\n", 3);
}

void push_b(t_list **a, t_list **b)
{
    push(a, b);
    write(1, "pb\n", 3);
}

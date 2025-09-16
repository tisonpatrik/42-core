/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_three.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: patrik <patrik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 00:00:00 by patrik            #+#    #+#             */
/*   Updated: 2025/09/16 21:40:58 by patrik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/ops.h"
#include "../../include/stack.h"

void	sort_three(t_sorting_state *ps)
{
	t_node	*a;
	t_node	*b;
	t_node	*c;
	int		x;
	int		y;
	int		z;

	if (get_size(ps->a) != 3)
		return ;
	a = get_head(ps->a);
	b = get_next(a);
	c = get_next(b);
	x = get_content(a);
	y = get_content(b);
	z = get_content(c);
	if (x < y && y < z)
		return ;
	if (x > y && y < z && x < z)
	{
		swap_a(ps);
		return ;
	}
	if (x > y && y > z)
	{
		swap_a(ps);
		reverse_rotate_a(ps);
		return ;
	}
	if (x > y && y < z && x > z)
	{
		rotate_a(ps);
		return ;
	}
	if (x < y && y > z && x < z)
	{
		swap_a(ps);
		rotate_a(ps);
		return ;
	}
	reverse_rotate_a(ps);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_push.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: patrik <patrik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 21:08:41 by ugerkens          #+#    #+#             */
/*   Updated: 2025/08/24 18:36:56 by patrik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/stack.h"

void	push(t_stack *src, t_stack *dest)
{
	int	dest_i;

	if (is_full(dest))
		return ;
	dest_i = next_up(dest, dest->top);
	dest->stack[dest_i] = src->stack[src->top];
	dest->top = dest_i;
	src->stack[src->top] = 0;
	src->top = next_down(src, src->top);
}

void	push_a(t_ps *data)
{
	push(&data->b, &data->a);
	if (data->writing_mode)
		save_op(data, pa);
}

void	push_b(t_ps *data)
{
	push(&data->a, &data->b);
	if (data->writing_mode)
		save_op(data, pb);
}

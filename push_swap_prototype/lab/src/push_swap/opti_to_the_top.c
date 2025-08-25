/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   opti_to_the_top.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: patrik <patrik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 21:08:20 by ugerkens          #+#    #+#             */
/*   Updated: 2025/08/25 12:42:50 by patrik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/push_swap.h"

void	chunk_to_the_top(t_ps *data, t_chunk *to_sort)
{

	if (to_sort->loc == BOTTOM_B && current_size(&data->b) == to_sort->size)
	{
		to_sort->loc = TOP_B;
	}
	if (to_sort->loc == BOTTOM_A && current_size(&data->a) == to_sort->size)
	{
		to_sort->loc = TOP_A;
	}
}

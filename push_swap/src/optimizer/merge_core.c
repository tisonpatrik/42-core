/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   merge_core.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: patrik <patrik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/19 20:49:37 by ptison            #+#    #+#             */
/*   Updated: 2025/09/19 23:17:51 by patrik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/optimizer.h"

t_operation	get_absorption_rr_rra(t_operation a)
{
	if (a == RR)
		return (RB);
	return (RRB);
}

t_operation	get_absorption_rr_rrb(t_operation a)
{
	if (a == RR)
		return (RA);
	return (RRA);
}

t_operation	get_absorption_rrr_ra(t_operation a)
{
	if (a == RRR)
		return (RRB);
	return (RB);
}

t_operation	get_absorption_rrr_rb(t_operation a)
{
	if (a == RRR)
		return (RRA);
	return (RA);
}

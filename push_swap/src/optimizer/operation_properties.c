/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operation_properties.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: patrik <patrik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 21:37:33 by patrik            #+#    #+#             */
/*   Updated: 2025/09/16 21:40:58 by patrik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/optimizer.h"


bool	touches_a(t_operation op)
{
	switch (op)
	{
		case SA:
		case RA:
		case RRA:
			return (true);
		default:
			return (false);
	}
}


bool	touches_b(t_operation op)
{
	switch (op)
	{
		case SB:
		case RB:
		case RRB:
			return (true);
		default:
			return (false);
	}
}

bool	is_barrier(t_operation op)
{
	switch (op)
	{
		case SS:
		case RR:
		case RRR:
		case PA:
		case PB:
			return (true);
		default:
			return (false);
	}
}


bool	is_pure_a(t_operation op)
{
	return (op == SA || op == RA || op == RRA);
}

bool	is_pure_b(t_operation op)
{
	return (op == SB || op == RB || op == RRB);
}

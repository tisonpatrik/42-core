/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_stroi.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omaly <student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/26 11:35:34 by omaly             #+#    #+#             */
/*   Updated: 2026/02/26 12:21:43 by omaly            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/conv.h"

int	ft_strtoi(const char *str, bool *error)
{
	long long	res;

	res = ft_atoll_safe(str, error);
	if (*error)
		return ((int)res);
	if (res > INT_MAX || res < INT_MIN)
	{
		*error = true;
		if (res > 0)
			return (INT_MAX);
		return (INT_MIN);
	}
	return ((int)res);
}

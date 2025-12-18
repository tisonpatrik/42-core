/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   converter.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptison <ptison@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/18 13:53:44 by ptison            #+#    #+#             */
/*   Updated: 2025/12/18 13:53:47 by ptison           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/validation.h"

static bool	is_numeric_str(const char *str)
{
	int	i;

	if (!str || !*str)
		return (false);
	i = 0;
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (false);
		i++;
	}
	return (true);
}

int	parse_positive_int(const char *str)
{
	unsigned long long int	nb;
	int						i;

	if (!is_numeric_str(str))
		return (-1);
	i = 0;
	nb = 0;
	while (str[i])
	{
		nb = nb * 10 + (str[i] - '0');
		if (nb > INT_MAX)
			return (-1);
		i++;
	}
	if (nb == 0)
		return (-1);
	return ((int)nb);
}

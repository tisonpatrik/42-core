/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoll_safe.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omaly <student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/26 11:36:25 by omaly             #+#    #+#             */
/*   Updated: 2026/02/26 12:26:45 by omaly            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/conv.h"

/*
** Checks for overflow before it happens.
** Handles the asymmetry of two's complement (LLONG_MIN vs LLONG_MAX).
*/
static int	check_overflow(unsigned long long acc, int sign, char next_digit)
{
	unsigned long long	cutoff;
	unsigned int		cutlim;

	if (sign < 0)
		cutoff = (unsigned long long)LLONG_MAX + 1;
	else
		cutoff = (unsigned long long)LLONG_MAX;
	cutlim = cutoff % 10;
	cutoff /= 10;
	if (acc > cutoff || (acc == cutoff && (unsigned int)(next_digit
			- '0') > cutlim))
		return (1);
	return (0);
}

static int	check_sign_and_inc(char c, int *sign)
{
	if (c == '+' || c == '-')
	{
		if (c == '-')
		{
			*sign = -1;
		}
		return (1);
	}
	return (0);
}

static long long	ft_atoll_safe_return(unsigned long long acc, bool error,
		int sign)
{
	if (error && sign == 1)
		return (LLONG_MAX);
	if (error && sign == -1)
		return (LLONG_MIN);
	return ((long long)(acc * sign));
}

/*
** Safe String-to-Long-Long conversion.
** Sets *error to true if:
** 1. String contains no digits.
** 2. String contains invalid characters (garbage).
** 3. Number overflows long long limits.
*/
long long	ft_atoll_safe(const char *str, bool *err)
{
	unsigned long long	acc;
	int					sign;
	int					i;

	acc = 0;
	sign = 1;
	i = 0;
	*err = false;
	while (ft_isspace(str[i]))
		i++;
	i += check_sign_and_inc(str[i], &sign);
	if (!ft_isdigit(str[i]))
		return (*err = true, 0);
	while (str[i] && ft_isdigit(str[i]))
	{
		if (check_overflow(acc, sign, str[i]))
			*err = true;
		acc = acc * 10 + (str[i] - '0');
		i++;
	}
	if (str[i] != '\0' && !ft_isspace(str[i]))
		*err = true;
	return (ft_atoll_safe_return(acc, *err, sign));
}

/*
** Wrapper for standard int behavior.
*/
int	ft_atoi(const char *str)
{
	bool	err;

	return ((int)ft_atoll_safe(str, &err));
}

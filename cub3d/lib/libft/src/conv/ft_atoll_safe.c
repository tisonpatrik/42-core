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

#include "conv.h"
#include "core.h"

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
	cutlim = (unsigned int)(cutoff % 10);
	cutoff /= 10;
	if (acc > cutoff || (acc == cutoff && (unsigned int)(next_digit
			- '0') > cutlim))
		return (1);
	return (0);
}

static int	parse_prefix(const char *str, int *sign)
{
	int	i;

	i = 0;
	while (ft_isspace(str[i]))
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			*sign = -1;
		i++;
	}
	return (i);
}

static long long	ft_atoll_safe_return(unsigned long long acc, bool error,
		int sign)
{
	if (error && sign == 1)
		return (LLONG_MAX);
	if (error && sign == -1)
		return (LLONG_MIN);
	if (sign < 0 && acc == (unsigned long long)LLONG_MAX + 1)
		return (LLONG_MIN);
	if (sign < 0)
		return (-(long long)acc);
	return ((long long)acc);
}

static void	check_trailing_characters(const char *str, int i, bool *err)
{
	while (ft_isspace(str[i]))
		i++;
	if (str[i] != '\0')
		*err = true;
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

	if (!err)
		return (0);
	*err = false;
	if (!str)
		return (*err = true, 0);
	acc = 0;
	sign = 1;
	i = parse_prefix(str, &sign);
	if (!ft_isdigit(str[i]))
		return (*err = true, 0);
	while (str[i] && ft_isdigit(str[i]))
	{
		if (check_overflow(acc, sign, str[i]))
			*err = true;
		acc = acc * 10 + (unsigned int)(str[i] - '0');
		i++;
	}
	check_trailing_characters(str, i, err);
	return (ft_atoll_safe_return(acc, *err, sign));
}

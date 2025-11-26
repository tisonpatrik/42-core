/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptison <ptison@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 21:49:31 by ptison            #+#    #+#             */
/*   Updated: 2025/09/27 11:37:35 by ptison           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/conv.h"
#include "../../include/core.h"

static int	get_sign(const char **current_position)
{
	int	sign;

	sign = 0;
	if (**current_position == '-')
	{
		sign = -1;
		(*current_position)++;
	}
	else if (**current_position == '+')
	{
		sign = 1;
		(*current_position)++;
	}
	else
		sign = 1;
	return (sign);
}

static void	skip_whitespace(const char **current_position)
{
	while (ft_isspace((unsigned char)**current_position))
		(*current_position)++;
}

static int	convert_number(const char *str, int idx)
{
	int	res;

	res = 0;
	while (ft_isdigit(str[idx]))
	{
		res = res * 10 + (str[idx] - '0');
		idx++;
	}
	return (res);
}

/**
 * @brief Converts a string to an integer (atoi)
 *
 * This function mimics the behavior of the standard atoi function.
 * It converts a string representation of a number to its integer value.
 * The function:
 * 1. Skips leading whitespace
 * 2. Handles optional '+' or '-' sign
 * 3. Converts consecutive digits to integer
 * 4. Ignores any trailing non-digit characters
 *
 * @param str The string to convert
 * @return The converted integer value
 *         0 if the string doesn't start with a valid number
 */
int	ft_atoi(const char *str)
{
	const char	*current_position;
	int			sign;
	int			res;

	current_position = str;
	res = 0;
	skip_whitespace(&current_position);
	sign = get_sign(&current_position);
	res = convert_number(current_position, 0);
	return (res * sign);
}
/*
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

int	main(void)
{
	char	*str;
	int		expected;
	int		current;

	str = "   -1234ab567";
	expected = atoi(str);
	current = ft_atoi(str);
	printf("expected: %d \n", expected);
	printf("current: %d \n", current);
	assert(expected == current);
}
*/

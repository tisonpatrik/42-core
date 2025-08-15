/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: patrik <patrik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 21:49:31 by ptison            #+#    #+#             */
/*   Updated: 2025/08/15 16:01:08 by patrik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	skip_whitespace(const char *str, int idx)
{
	while (str[idx] == ' ' || str[idx] == '\t' || str[idx] == '\n'
		|| str[idx] == '\v' || str[idx] == '\f' || str[idx] == '\r')
		idx++;
	return (idx);
}

int	convert_number(const char *str, int idx)
{
	int	res;
	int	digit;

	res = 0;
	while (str[idx] >= '0' && str[idx] <= '9')
	{
		digit = str[idx] - '0';
		if (res > 2147483647 / 10 || (res == 2147483647 / 10 && digit > 7))
			return (0);
		res = res * 10 + digit;
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
 * 4. Checks for integer overflow and returns 0 if overflow occurs
 * 5. Ignores any trailing non-digit characters
 *
 * @param str The string to convert
 * @return The converted integer value
 *         0 if the string doesn't start with a valid number or if overflow occurs
 */
int	ft_atoi(const char *str)
{
	int	idx;
	int	sign;
	int	res;

	idx = 0;
	sign = 1;
	res = 0;
	idx = skip_whitespace(str, idx);
	if (str[idx] == '-' || str[idx] == '+')
	{
		if (str[idx] == '-')
			sign = -1;
		idx++;
	}
	res = convert_number(str, idx);
	if (res == 0 && str[idx] >= '0' && str[idx] <= '9')
		return (0);
	if (sign == -1 && res > 2147483647)
		return (0);
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

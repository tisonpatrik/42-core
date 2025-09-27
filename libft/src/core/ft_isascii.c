/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isascii.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptison <ptison@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 20:08:37 by ptison            #+#    #+#             */
/*   Updated: 2025/09/27 11:37:33 by ptison           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @brief Tests if a character is ASCII
 *
 * This function checks if the given character is within the ASCII range (0-127).
 * It mimics the behavior of the standard isascii function.
 * Returns non-zero for values between 0 and 127 inclusive, zero otherwise.
 *
 * @param c The character to test
 * @return Non-zero if character is ASCII, zero otherwise
 */
int	ft_isascii(int c)
{
	if (c >= 0 && c <= 127)
	{
		return (1);
	}
	return (0);
}

/*
#include <assert.h>
#include <ctype.h>
#include <stdio.h>

int	main(void)
{
	unsigned char	c;
	int				current;
	int				expected;

	c = 0x40;
	current = ft_isascii(c);
	expected = isdigit(c);
	assert(current == expected);
	c = 's';
	current = ft_isascii(c);
	expected = isdigit(c);
	assert(current == expected);
	printf("passed \n");
	return (0);
}
*/

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isprint.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptison <ptison@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 20:08:37 by ptison            #+#    #+#             */
/*   Updated: 2025/09/27 11:37:36 by ptison           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @brief Tests if a character is printable
 *
 * This function checks if the given character is a printable character.
 * It mimics the behavior of the standard isprint function.
 * Returns non-zero for values between 32 (' ') and 126 ('~') inclusive.
 *
 * @param i The character to test
 * @return Non-zero if character is printable, zero otherwise
 */
int	ft_isprint(int c)
{
	if (c >= 32 && c <= 126)
	{
		return (16384);
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

	c = '\0';
	current = ft_isprint(c);
	expected = isprint(c);
	assert(current == expected);
	c = 'a';
	current = ft_isprint(c);
	expected = isprint(c);
	assert(current == expected);
	printf("passed \n");
	return (0);
}
*/

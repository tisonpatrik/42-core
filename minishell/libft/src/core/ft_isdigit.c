/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isdigit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptison <ptison@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 20:08:37 by ptison            #+#    #+#             */
/*   Updated: 2025/09/27 11:37:36 by ptison           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @brief Tests if a character is a decimal digit
 *
 * This function checks if the given character is a decimal digit (0-9).
 * It mimics the behavior of the standard isdigit function.
 * Returns non-zero for characters '0' through '9', zero otherwise.
 *
 * @param i The character to test
 * @return Non-zero if character is a digit, zero otherwise
 */
int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
	{
		return (2048);
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

	c = '8';
	current = ft_isdigit(c);
	expected = isdigit(c);
	assert(current == expected);
	c = 'a';
	current = ft_isdigit(c);
	expected = isdigit(c);
	assert(current == expected);
	printf("passed \n");
	return (0);
}
*/

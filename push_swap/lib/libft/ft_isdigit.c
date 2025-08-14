/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isdigit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: patrik <patrik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 17:37:15 by ptison            #+#    #+#             */
/*   Updated: 2025/05/26 18:58:50 by patrik           ###   ########.fr       */
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
int	ft_isdigit(unsigned char i)
{
	if (i >= '0' && i <= '9')
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

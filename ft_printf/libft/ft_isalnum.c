/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalnum.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: patrik <patrik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 20:08:37 by ptison            #+#    #+#             */
/*   Updated: 2025/05/26 18:58:50 by patrik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @brief Tests if a character is alphanumeric
 *
 * This function checks if the given character is alphanumeric.
 * It mimics the behavior of the standard isalnum function.
 * Returns non-zero for characters a-z, A-Z, and 0-9, zero otherwise.
 *
 * @param c The character to test
 * @return Non-zero if character is alphanumeric, zero otherwise
 */
int	ft_isalnum(unsigned char c)
{
	if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z'))
	{
		return (8);
	}
	else if (c >= '0' && c <= '9')
	{
		return (8);
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

	c = 'h';
	current = ft_isalnum(c);
	expected = isalnum(c);
	printf("current: %d, expected: %d \n", current, expected);
	assert(current == expected);
	printf("passed \n");
	return (0);
}
*/

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalpha.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptison <ptison@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 20:08:37 by ptison            #+#    #+#             */
/*   Updated: 2025/09/23 11:32:58 by ptison           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @brief Tests if a character is alphabetic
 *
 * This function checks if the given character is an alphabetic character.
 * It mimics the behavior of the standard isalpha function.
 * Returns non-zero for characters a-z and A-Z, zero otherwise.
 *
 * @param c The character to test
 * @return Non-zero if character is alphabetic, zero otherwise
 */
int	ft_isalpha(int c)
{
	if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z'))
	{
		return (1024);
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

	c = 'a';
	current = ft_isalpha(c);
	expected = isalpha(c);
	assert(current == expected);
	printf("passed \n");
	return (0);
}
*/

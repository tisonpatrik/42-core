/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tolower.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: patrik <patrik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 19:39:03 by ptison            #+#    #+#             */
/*   Updated: 2025/05/26 18:58:50 by patrik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @brief Converts a character to lowercase
 *
 * This function converts an uppercase letter to its lowercase equivalent.
 * It mimics the behavior of the standard tolower function.
 * If the character is not an uppercase letter, it is returned unchanged.
 *
 * @param ch The character to convert
 * @return The lowercase equivalent if ch is uppercase, ch otherwise
 */
int	ft_tolower(int ch)
{
	if (ch >= 'A' && ch <= 'Z')
	{
		return (ch + 32);
	}
	return (ch);
}

/*
#include <assert.h>
#include <ctype.h>
#include <stdio.h>

int	main(void)
{
	int	upper;
	int	expected;
	int	current;

	upper= 'Z';
	expected = tolower(upper);
	printf("expected --> big: %c  , small: %c \n", upper, expected);
	current = ft_tolower(upper);
	printf("current --> big: %c  , small: %c \n", upper, current);
	assert(expected == current);
	return (1);
}
*/

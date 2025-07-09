/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_toupper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptison <ptison@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 18:52:06 by ptison            #+#    #+#             */
/*   Updated: 2025/06/19 19:32:18 by ptison           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @brief Converts a character to uppercase
 *
 * This function converts a lowercase letter to its uppercase equivalent.
 * It mimics the behavior of the standard toupper function.
 * If the character is not a lowercase letter, it is returned unchanged.
 *
 * @param ch The character to convert
 * @return The uppercase equivalent if ch is lowercase, ch otherwise
 */
int	ft_toupper(int ch)
{
	if (ch >= 'a' && ch <= 'z')
	{
		return (ch - 32);
	}
	return (ch);
}

/*
#include <assert.h>
#include <ctype.h>
#include <stdio.h>

int	main(void)
{
	int	lower;
	int	upper;
	int	current;

	lower = 'a';
	upper = toupper(lower);
	printf("expected --> small: %c  , big: %c \n", lower, upper);
	current = ft_toupper(lower);
	printf("current --> small: %c  , big: %c \n", lower, current);
	assert(upper == current);
	return (1);
}
*/

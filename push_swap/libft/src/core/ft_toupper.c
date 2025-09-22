/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_toupper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: patrik <patrik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 20:08:37 by ptison            #+#    #+#             */
/*   Updated: 2025/09/16 21:40:58 by patrik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/core.h"

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
int	ft_toupper(int c)
{
	if (c >= 'a' && c <= 'z')
	{
		return (c - 32);
	}
	return (c);
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

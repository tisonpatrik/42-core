/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: patrik <patrik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 21:12:25 by ptison            #+#    #+#             */
/*   Updated: 2025/05/26 18:58:50 by patrik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @brief Calculates the length of a string
 *
 * This function counts the number of characters in a null-terminated string.
 * It mimics the behavior of the standard strlen function.
 * The function counts characters until it encounters the null terminator '\0'.
 *
 * @param str The string whose length is to be calculated
 * @return The number of characters in the string (excluding null terminator)
 */

#include <stddef.h>

size_t	ft_strlen(const char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		i++;
	}
	return (i);
}

/*
#include <assert.h>
#include <stdio.h>
#include <string.h>

int	main(void)
{
	int	expected;
	int	current;

	char* str = "pico";
	expected = strlen(str);
	current = ft_strlen(str);
	assert(expected == current);
	printf("passed \n");
	return (0);
}

*/

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: patrik <patrik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/25 23:06:59 by patrik            #+#    #+#             */
/*   Updated: 2025/05/26 18:58:50 by patrik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @brief Applies a function to each character of a string with index
 *
 * This function applies the function 'f' to each character of the
 * string 's', passing its index as first argument. Each character is
 * passed by address to 'f' to be modified if necessary.
 *
 * @param s The string on which to iterate
 * @param f The function to apply to each character and its index
 */
void	ft_striteri(char *s, void (*f)(unsigned int, char *))
{
	unsigned int	i;

	if (!s || !f)
		return ;
	i = 0;
	while (s[i])
	{
		f(i, &s[i]);
		i++;
	}
}

/*
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void	to_upper_iter(unsigned int i, char *c)
{
	(void)i;
	*c = (char)toupper((unsigned char)*c);
}

int	main(void)
{
	char	*str = strdup("Hello");
	if (!str)
		return (1);

	printf("Original: %s\n", str);
	ft_striteri(str, to_upper_iter);
	printf("Mapped:   %s\n", str);
	free(str);
	return (0);
}
*/

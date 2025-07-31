/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: patrik <patrik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/25 22:52:23 by patrik            #+#    #+#             */
/*   Updated: 2025/05/26 19:00:23 by patrik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

static int	get_len(int n)
{
	int	len;

	len = (n <= 0);
	while (n)
	{
		len++;
		n /= 10;
	}
	return (len);
}

/**
 * @brief Converts an integer to a string
 *
 * This function allocates and returns a string representing the integer
 * received as an argument. Negative numbers are handled correctly.
 * Memory for the new string is obtained with malloc and can be freed with free.
 *
 * @param n The integer to convert
 * @return The string representing the integer, or NULL if allocation fails
 */
char	*ft_itoa(int n)
{
	char	*str;
	int		len;
	long	nb;

	nb = n;
	len = get_len(n);
	str = (char *)malloc(sizeof(char) * (len + 1));
	if (!str)
		return (NULL);
	str[len] = '\0';
	if (nb < 0)
	{
		str[0] = '-';
		nb = -nb;
	}
	if (nb == 0)
		str[0] = '0';
	while (nb)
	{
		str[--len] = (nb % 10) + '0';
		nb /= 10;
	}
	return (str);
}

/*
#include <unistd.h>
int main(void)
{
	int n = 666;
	char *str = ft_itoa(n);
	for(int i=0; str[i]; i++ )
	{
		write(1, &str[i], 1);
	}
	write(1, "\n", 1);
}
*/

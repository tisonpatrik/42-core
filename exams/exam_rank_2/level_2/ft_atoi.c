/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptison <ptison@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/28 19:22:26 by ptison            #+#    #+#             */
/*   Updated: 2025/10/28 20:17:47 by ptison           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include <stdio.h>

int	get_len(const char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

int	get_start(const char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!(str[i] == ' ' || str[i] == '	'))
			break ;
		i++;
	}
	return (i);
}

int	ft_atoi(const char *str)
{
	int		len;
	int		result;
	int		nbr;
	int		i;
	bool	have_sign;
	bool	is_minus;
	int		start;

	len = get_len(str) - 1;
	start = get_start(str);
	result = 0;
	i = 1;
	have_sign = false;
	is_minus = false;
	while (len >= start)
	{
		if (str[len] > '0' && str[len] < '9')
		{
			nbr = str[len] - '0';
			if (i == 1)
			{
				result = result + nbr;
			}
			else
			{
				result = i * nbr + result;
			}
			i = i * 10;
		}
		else if (str[len] == '-')
		{
			if (have_sign)
				return (0);
			have_sign = true;
			is_minus = true;
		}
		else if (str[len] == '+')
		{
			if (have_sign)
				return (0);
			have_sign = true;
			is_minus = false;
		}
		else
		{
			return (0);
		}
		len--;
	}
	if (is_minus)
		result = result * (-1);
	return (result);
}

int	main(int ac, char **av)
{
	int	number;

	number = ft_atoi(av[1]);
	printf("%d\n", number);
	return (0);
}

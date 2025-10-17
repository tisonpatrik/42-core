/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptison <ptison@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 23:55:32 by ptison            #+#    #+#             */
/*   Updated: 2025/10/18 01:08:05 by ptison           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../include/utils.h"


int	hex_to_int(const char *hex_str)
{
	int	result;
	int	i;

	result = 0;
	i = 0;
	while (hex_str[i])
	{
		result *= 16;
		if (hex_str[i] >= '0' && hex_str[i] <= '9')
			result += hex_str[i] - '0';
		else if (hex_str[i] >= 'A' && hex_str[i] <= 'F')
			result += hex_str[i] - 'A' + 10;
		else if (hex_str[i] >= 'a' && hex_str[i] <= 'f')
			result += hex_str[i] - 'a' + 10;
		i++;
	}
	return (result);
}

void	fdf_error(const char *message)
{
	if (errno == 0)
	{
		ft_putstr_fd("FdF: ", 2);
		ft_putendl_fd((char *)message, 2);
	}
	else
		perror("FdF");
	exit(1);
}
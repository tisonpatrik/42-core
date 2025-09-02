/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: patrik <patrik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 21:00:44 by ptison            #+#    #+#             */
/*   Updated: 2025/09/02 13:45:22 by patrik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/validator.h"
#include <stdlib.h>
#include <unistd.h>

void	free_array(char **splitted)
{
	int	i;

	i = 0;
	if (!splitted)
	{
		return ;
	}
	while (splitted[i] != NULL)
	{
		free(splitted[i]);
		i++;
	}
	free(splitted);
}

void	fatal_cleanup_and_exit(int *buf, char **tmp)
{
	if (tmp)
		free_array(tmp);
	free(buf);
	write(2, "Error\n", 6);
	exit(1);
}

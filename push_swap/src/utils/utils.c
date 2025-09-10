/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: patrik <patrik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 21:00:44 by ptison            #+#    #+#             */
/*   Updated: 2025/09/10 22:07:04 by patrik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/validator.h"
#include <stdlib.h>
#include <unistd.h>

void	fatal_cleanup_and_exit(int *buf, char **tmp)
{
	if (tmp)
		ft_free_array(tmp);
	free(buf);
	write(2, "Error\n", 6);
	exit(1);
}

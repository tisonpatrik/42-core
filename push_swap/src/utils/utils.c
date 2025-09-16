/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptison <ptison@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 20:38:58 by ptison            #+#    #+#             */
/*   Updated: 2025/09/16 20:39:01 by ptison           ###   ########.fr       */
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

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptison <ptison@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/28 14:44:49 by ptison            #+#    #+#             */
/*   Updated: 2025/09/28 14:45:24 by ptison           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/validator.h"

void	fatal_cleanup_and_exit(int *buf, char **tmp)
{
	if (buf)
		free(buf);
	if (tmp)
		ft_free_array(tmp);
	ft_putstr_fd("Error\n", 2);
	exit(1);
}

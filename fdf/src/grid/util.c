/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptison <ptison@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/27 16:40:00 by ptison            #+#    #+#             */
/*   Updated: 2025/10/19 21:13:20 by ptison           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../include/grid.h"

int	get_file_fd(const char *file_name)
{
	int	fd;

	fd = open(file_name, O_RDONLY);
	if (fd < 0)
	{
		perror("open");
		return (-1);
	}
	return (fd);
}


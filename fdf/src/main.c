/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptison <ptison@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/26 15:49:35 by ptison            #+#    #+#             */
/*   Updated: 2025/09/26 16:37:36 by ptison           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/libft/include/libft.h"
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>

int	get_file_descriptor(char *file_name)
{
	int	fd;

	fd = open(file_name, O_RDONLY);
	if (fd < 0)
	{
		perror("open");
		exit(EXIT_FAILURE);
	}
	printf("%d \n", fd);
	return (fd);
}

void	get_map(char *file_name)
{
	int		fd;
	char	*line;

	fd = get_file_descriptor(file_name);
	while (true)
	{
		line = ft_get_line(fd);
		if (line == NULL)
		{
			break ;
		}
		printf("%s \n", line);
	}
}

int	main(int argc, char **argv)
{
	if (argc != 2)
	{
		return (EXIT_FAILURE);
	}
	get_map(argv[1]);
	return (EXIT_SUCCESS);
}

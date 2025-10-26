/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptison <ptison@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/27 11:37:00 by ptison            #+#    #+#             */
/*   Updated: 2025/10/26 11:06:55 by ptison           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/app.h"

bool	has_fdf_extension(const char *filename)
{
	size_t		len;
	const char	*ext = ".fdf";
	size_t		ext_len;

	len = ft_strlen(filename);
	ext_len = 4;
	if (len < ext_len)
	{
		return (false);
	}
	return (ft_strncmp(filename + (len - ext_len), ext, ext_len) == 0);
}

int	main(int argc, char **argv)
{
	t_app	*app;

	if (argc != 2)
	{
		handle_error("Usage: ./fdf <map_file>\n");
	}
	if (!has_fdf_extension(argv[1]))
	{
		handle_error("Only .fdf files are allowed\n");
	}
	app = init_app(argv[1]);
	if (!app)
	{
		handle_error("Failed to initialize new app\n");
	}
	run_app(app);
	free_app(app);
	return (0);
}

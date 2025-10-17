/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptison <ptison@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/27 11:37:00 by ptison            #+#    #+#             */
/*   Updated: 2025/10/17 23:13:51 by ptison           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../include/old_app.h"
# include "../include/app.h"

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



int32_t	main(int argc, char **argv)
{

	if (argc != 2)
	{
		ft_putstr_fd("Usage: ./fdf <map_file>\n", STDERR_FILENO);
		return (EXIT_FAILURE);
	}
	if (!has_fdf_extension(argv[1]))
	{
		ft_putstr_fd("Only .fdf files are allowed\n", STDERR_FILENO);
		return (EXIT_FAILURE);
	}
	
	// t_fdf *fdf = init_fdf(argv[1]);
	// run_fdf(fdf);
	// mlx_terminate(fdf->mlx);
	// destroy_map(fdf->view);

	t_app *app = init_app(argv[1]);
	if (!app)
	{
		ft_putstr_fd("Failed to initialize app\n", STDERR_FILENO);
		return (EXIT_FAILURE);
	}
	run_app(app);
	free_app(app);


	return (0);
}
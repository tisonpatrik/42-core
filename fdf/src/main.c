/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptison <ptison@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/27 11:37:00 by ptison            #+#    #+#             */
/*   Updated: 2025/10/17 23:52:04 by ptison           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../include/app.h"
# include "../include/old_app.h"

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


void run_new_implementation(char *filename)
{
	t_app *app = init_app(filename);
	if (!app)
	{
		ft_putstr_fd("Failed to initialize new app\n", STDERR_FILENO);
		return;
	}
	run_app(app);
	free_app(app);
}

void run_old_implementation(char *filename)
{
	t_fdf *fdf = init_fdf(filename);
	if (!fdf)
	{
		ft_putstr_fd("Failed to initialize old fdf\n", STDERR_FILENO);
		return;
	}
	run_fdf(fdf);
	free_view(fdf->view);
	mlx_terminate(fdf->mlx);
	free(fdf);
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
	
	
	// run_new_implementation(argv[1]);
	run_old_implementation(argv[1]);

	return (0);
}
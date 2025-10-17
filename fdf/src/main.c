/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptison <ptison@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/27 11:37:00 by ptison            #+#    #+#             */
/*   Updated: 2025/10/17 20:42:25 by ptison           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../include/old_app.h"
# include "../include/experimental.h"
# include "../include/camera.h"

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

void	compare_grids(t_grid *standard_grid, t_grid *experimental_grid)
{
	printf("=== GRID COMPARISON ===\n");
	printf("Standard Grid:\n");
	printf("  Rows: %d, Cols: %d\n", standard_grid->rows, standard_grid->cols);
	printf("  High: %d, Low: %d\n", standard_grid->high, standard_grid->low);
	printf("  Grid3D: %p\n", (void*)standard_grid->grid3d);
	printf("  Arena: %p\n", (void*)standard_grid->arena);
	
	printf("\nExperimental Grid:\n");
	printf("  Rows: %d, Cols: %d\n", experimental_grid->rows, experimental_grid->cols);
	printf("  High: %d, Low: %d\n", experimental_grid->high, experimental_grid->low);
	printf("  Grid3D: %p\n", (void*)experimental_grid->grid3d);
	printf("  Arena: %p\n", (void*)experimental_grid->arena);
	
	printf("\n=== DETAILED COMPARISON ===\n");
	if (standard_grid->rows == experimental_grid->rows && 
		standard_grid->cols == experimental_grid->cols)
	{
		printf("✓ Dimensions match\n");
		
		// Compare ALL points
		int total_points = standard_grid->rows * standard_grid->cols;
		int matching_points = 0;
		int different_points = 0;
		
		printf("\nComparing ALL %d points:\n", total_points);
		
		for (int i = 0; i < standard_grid->rows; i++)
		{
			for (int j = 0; j < standard_grid->cols; j++)
			{
				t_point3d *std_point = &standard_grid->grid3d[i][j];
				t_point3d *exp_point = &experimental_grid->grid3d[i][j];
				
				bool coords_match = (std_point->x == exp_point->x && 
									std_point->y == exp_point->y && 
									std_point->z == exp_point->z);
				
				if (coords_match)
					matching_points++;
				else
				{
					different_points++;
					if (different_points <= 5) // Show first 5 differences
					{
						printf("DIFF[%d][%d]: std(%.2f,%.2f,%.2f) vs exp(%.2f,%.2f,%.2f)\n", 
							i, j, std_point->x, std_point->y, std_point->z,
							exp_point->x, exp_point->y, exp_point->z);
					}
				}
			}
		}
		
		printf("\nSUMMARY:\n");
		printf("  Matching points: %d/%d (%.1f%%)\n", 
			matching_points, total_points, (double)matching_points/total_points*100);
		printf("  Different points: %d/%d (%.1f%%)\n", 
			different_points, total_points, (double)different_points/total_points*100);
		
		if (matching_points == total_points)
			printf("  ✓ ALL POINTS MATCH PERFECTLY!\n");
		else
			printf("  ✗ Some points differ\n");
	}
	else
	{
		printf("✗ Dimensions differ\n");
	}
	printf("========================\n\n");
}


int32_t	main(int argc, char **argv)
{
	t_fdf		*fdf;

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
	
	fdf = init_fdf(argv[1]);

	t_heightmap *heightmap = read_heightmap_from_file(argv[1]);
	t_camera camera;
	t_grid *grid;
	
	init_camera_defaults(&camera);
	set_camera_isometric(&camera, WIDTH, HEIGHT);
	grid = get_grid(heightmap);
	compare_grids(&fdf->view->grid, grid);

	if (!grid)
	{
		ft_putstr_fd("Failed to create grid\n", STDERR_FILENO);
		return (EXIT_FAILURE);
	}

	// Compare standard grid (from fdf->view) with experimental grid

	run_app(fdf);
	mlx_terminate(fdf->mlx);
	destroy_map(fdf->view);

	return (0);
}
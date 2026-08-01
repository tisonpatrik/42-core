#include "parsing.h"

void	input_control(int argc, char *title)
{
	char	*cub_ptr;

	if (argc != 2)
		error_exit("Usage: ./cub3d <path/scene_title.cub>");
	if (ft_strlen(title) < 5)
		error_exit("Scene file format <title.cub>");
	cub_ptr = title + (ft_strlen(title) - 4);
	if (ft_strncmp(cub_ptr, ".cub", 4) != 0)
		error_exit("Scene file format <title.cub>");
}

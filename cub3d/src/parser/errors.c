#include "parsing.h"

void	display_error(char *msg)
{
	ft_putendl_fd("Error", 2);
	ft_putendl_fd(msg, 2);
}

void	error_free_exit(char *msg, t_scene_config *cfg, t_file *file)
{
	if (msg != NULL)
		display_error(msg);
	if (cfg)
		free_scene_cfg(cfg);
	if (file)
		free_file(file);
	exit(EXIT_FAILURE);
}

void	error_exit(char *msg)
{
	display_error(msg);
	exit(EXIT_FAILURE);
}

#include <stdlib.h>
#include "game.h"
#include "mem.h"
#include "parsing.h"

int	main(int argc, char *argv[])
{
	t_game			game;
	t_scene_config	config;
	int				status;

	ft_bzero(&game, sizeof(game));
	input_control(argc, argv[1]);
	if (parse_scene_cfg(argv[1], &config) != EXIT_SUCCESS)
		return (EXIT_FAILURE);
	status = game_setup(&game, &config);
	free_scene_cfg(&config);
	if (status != EXIT_SUCCESS)
		return (EXIT_FAILURE);
	status = run_engine(&game);
	game_cleanup(&game);
	return (status);
}

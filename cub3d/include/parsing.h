#ifndef PARSING_H
# define PARSING_H

# include <errno.h>
# include <fcntl.h>
# include <stdint.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include "libft.h"

# define CUB_EXTENSION ".cub"
# define CUB_EXTENSION_LEN 4
# define WHITE " \t\n\r\v\f"
# define SPACE " "
# define EOFCHARS "\n\r"
# define MAPCHARS "012NSEW "
# define PLAYER "NSEW"
# define TEXRGBSTART "NSWEFC"

typedef struct s_map
{
	char	**grid;
	int		rows;
	int		max_cols;
	int		p_y;
	int		p_x;
	char	p_dir;
}t_map;

typedef struct s_file
{
	char	**lines;
	int		line_count;
	int		index;
	t_map	map;
}t_file;

typedef struct s_wall_paths
{
	char	*north;
	char	*south;
	char	*west;
	char	*east;
}t_wall_paths;

/* Parser-owned fields are released by free_scene_cfg after game_setup. */
typedef struct s_scene_config
{
	t_v2i			map_size;
	uint8_t			*tiles;
	t_v2d			spawn_position;
	t_v2d			spawn_direction;
	t_v2d			camera_plane;
	t_wall_paths	wall_paths;
	t_rgba			floor_color;
	t_rgba			ceiling_color;
}t_scene_config;

int		check_store_player(t_map *map);
int		check_walls(t_map *map);
int		empty_line(char *line);
void	erase_white_eof(char *line, char *macro_type);
int		fill_rest_cfg(t_map *map, t_scene_config *cfg);
int		is_map_line(char *line);
void	init_scene_cfg(t_scene_config *cfg);
t_file	init_file(char *file_name, t_scene_config *cfg);
void	input_control(int argc, char *title);
int		is_after_map_empty(t_file *file);
int		is_config_complete(t_scene_config *cfg);
int		is_in(char c, char *set);
int		is_map_start(t_file *file, t_scene_config *cfg);
int		load_map(t_file *file, t_scene_config *cfg);
int		parse_store_config(char *line, t_scene_config *cfg, t_file *file);
int		parse_rgb(char *line, t_rgba *rgb, char c, t_scene_config *cfg);
int		parse_scene_cfg(char *file_name, t_scene_config *cfg);
int		parse_texture(char *line, char **path, char c);
int		validate_map(t_file *file, t_scene_config *cfg);
void	error_exit(char *msg);
void	error_free_exit(char *msg, t_scene_config *cfg, t_file *file);
void	display_error(char *msg);
void	free_file(t_file *file);
void	free_map(t_map *map);
void	free_scene_cfg(t_scene_config *cfg);

#endif

#ifndef ROM_H
# define ROM_H

# include <stdbool.h>
# include "MLX42.h"
# include "color.h"
# include "vec2.h"

struct	s_scene_config;

typedef enum e_wall_texture
{
	TEX_NORTH,
	TEX_SOUTH,
	TEX_WEST,
	TEX_EAST,
	TEX_WALL_COUNT
}	t_wall_texture;

typedef struct s_texture_set
{
	mlx_texture_t	*wall[TEX_WALL_COUNT];
	mlx_texture_t	*fire;
	mlx_texture_t	*scorch;
	mlx_texture_t	*orb;
}	t_texture_set;

typedef struct s_rom
{
	t_v2i			map_size;
	t_rgba			floor_color;
	t_rgba			ceiling_color;
	bool			bonus_enabled;
	t_texture_set	textures;
}	t_rom;

bool	texture_load_png(mlx_texture_t **destination, const char *path,
			const char *name);
bool	textures_load_bonus(t_texture_set *textures);
int		textures_load(t_texture_set *textures,
			const struct s_scene_config *config, bool bonus_enabled);
void	textures_cleanup(t_texture_set *textures);

#endif

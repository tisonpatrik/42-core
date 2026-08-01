#include "rom.h"
#include "io.h"
#include "orb.h"

#define FIRE_TEXTURE_PATH "./assets/cub3d/fire_0.png"
#define SCORCH_TEXTURE_PATH "./assets/cub3d/scorched_ground.png"
#define ORB_TEXTURE_PATH "./assets/cub3d/experience_orb.png"

static bool	valid_fire_sheet(mlx_texture_t *texture)
{
	if (!texture || texture->width == 0)
		return (false);
	return (texture->height >= texture->width
		&& texture->height % texture->width == 0);
}

static bool	valid_orb_atlas(mlx_texture_t *texture)
{
	uint32_t	frame_width;
	uint32_t	frame_height;

	frame_width = texture->width / ORB_ATLAS_COLUMNS;
	frame_height = texture->height / ORB_ATLAS_ROWS;
	return (texture->width % ORB_ATLAS_COLUMNS == 0
		&& texture->height % ORB_ATLAS_ROWS == 0
		&& frame_width > 0 && frame_width == frame_height);
}

bool	textures_load_bonus(t_texture_set *textures)
{
	if (!texture_load_png(&textures->fire, FIRE_TEXTURE_PATH, "fire texture"))
		return (false);
	if (!valid_fire_sheet(textures->fire))
		return (ft_putendl_fd("Error\nInvalid fire texture sheet.", 2), false);
	if (!texture_load_png(&textures->scorch, SCORCH_TEXTURE_PATH,
			"scorch texture")
		|| !texture_load_png(&textures->orb, ORB_TEXTURE_PATH, "orb texture"))
		return (false);
	if (!valid_orb_atlas(textures->orb))
		return (ft_putendl_fd("Error\nInvalid orb texture atlas.", 2), false);
	return (true);
}

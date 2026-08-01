#ifndef RENDERER_H
# define RENDERER_H

# include <stdint.h>
# include "MLX42.h"
# include "color.h"
# include "config.h"
# include "orb.h"
# include "ray.h"
# include "vec2.h"

struct	s_game;

# define RENDER_NEAR_DISTANCE 0.001
# define MM_MAX_SCALE 8
# define MM_MIN_SCALE 2
# define MM_MARGIN 20
# define MM_PANEL_PADDING 5

enum e_render_constants
{
	FLOOR_ROW_COUNT = WINDOW_HEIGHT - WINDOW_HEIGHT / 2 - 1,
	MM_MAX_PANEL_WIDTH = WINDOW_WIDTH / 3,
	MM_MAX_PANEL_HEIGHT = WINDOW_HEIGHT / 3
};

typedef enum e_minimap_color
{
	MM_COLOR_PANEL,
	MM_COLOR_WALL,
	MM_COLOR_FLOOR,
	MM_COLOR_FIRE,
	MM_COLOR_SCORCH,
	MM_COLOR_PLAYER,
	MM_COLOR_ORB
}	t_minimap_color;

typedef struct s_draw
{
	int			projected_height;
	int			screen_top;
	int			screen_bottom;
	int			texture_x;
	int			texture_y;
	double		texture_y_step;
	double		texture_y_position;
}	t_draw;

typedef struct s_minimap_view
{
	t_v2i	first_tile;
	t_v2i	visible_tiles;
	t_v2i	grid_origin;
	int		tile_scale;
}	t_minimap_view;

typedef struct s_orb_projection
{
	double	depth;
	int		size;
	int		left;
	int		right;
	int		top;
	int		bottom;
}	t_orb_projection;

t_rgba_view		image_rgba_view(mlx_image_t *image);
t_rgba_view		texture_rgba_view(mlx_texture_t *texture);
void			render_frame(struct s_game *game);
void			render_background(struct s_game *game);
void			blend_pixel(t_rgba_ref destination, t_rgba source);
void			cast_ray(struct s_game *game, int screen_x, t_ray *ray,
					t_hit_buffer *hits);
void			calc_wall_projection(t_draw *draw, double distance);
mlx_texture_t	*get_wall_texture(struct s_game *game, t_ray *ray);
int				texture_column(const t_ray_hit *hit, t_v2d direction,
					int width);
void			calc_texture_mapping(t_draw *draw, t_ray *ray,
					mlx_texture_t *texture);
void			draw_wall_column(struct s_game *game, int x, t_draw *draw,
					mlx_texture_t *texture);
void			draw_fire_column(struct s_game *game, int x, t_ray *ray,
					t_ray_hit *hit);
void			render_scorch_column(struct s_game *game, int x, t_ray *ray,
					const double *row_distances);
void			render_minimap(struct s_game *game);
t_rgba			minimap_color(t_minimap_color color);
void			minimap_draw_rectangle(struct s_game *game, t_v2i position,
					t_v2i size, t_rgba color);
t_rgba			minimap_tile_color(struct s_game *game, t_v2i map);
void			minimap_draw_player(struct s_game *game,
					t_minimap_view *view);
void			minimap_draw_orbs(struct s_game *game, t_minimap_view *view);
t_v2i			minimap_world_to_pixel(const t_minimap_view *view,
					t_v2d position);
void			render_orbs(struct s_game *game);
void			draw_projected_orb(struct s_game *game,
					const t_orb_projection *projection);

#endif

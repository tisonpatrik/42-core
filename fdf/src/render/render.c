
# include "../../include/renderer.h"

t_renderer	init_renderer(void)
{
	t_renderer	renderer;

	renderer.mlx = mlx_init(WIDTH, HEIGHT, "FdF", true);
	renderer.img = mlx_new_image(renderer.mlx, WIDTH, HEIGHT);
	renderer.width = WIDTH;
	renderer.height = HEIGHT;
	return (renderer);
}

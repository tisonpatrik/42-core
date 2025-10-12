/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   app.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptison <ptison@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/10 13:36:16 by ptison            #+#    #+#             */
/*   Updated: 2025/10/12 22:05:22 by ptison           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef APP_H
# define APP_H

# include "types.h"
# include "map.h"
# include "utils.h"
# include "render.h"
# include "view.h"
# include "../lib/libft/include/libft.h"
# include "../lib/MLX42/include/MLX42/MLX42.h"

# define WIDTH				1920
# define HEIGHT				1080

typedef struct s_app
{
	mlx_t		*mlx;
	t_map		*map;
	mlx_image_t	*image;
	t_view	*view;
}				t_app;

t_app	app_init(const char *file_name);
void	app_run(t_app *app);
void	free_app(t_app app);

void	handle_keybinds(void *param);
void	handle_rotate(void *param);
void	handle_projection(void *param);
void	handle_scroll(double xdelta, double ydelta, void *param);

#endif

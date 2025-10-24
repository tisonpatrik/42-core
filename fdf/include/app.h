/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   app.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptison <ptison@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 20:45:19 by ptison            #+#    #+#             */
/*   Updated: 2025/10/24 09:32:45 by ptison           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef APP_H
# define APP_H

# include "../include/camera.h"
# include "../include/grid.h"
# include "../include/renderer.h"
# include "../lib/MLX42/include/MLX42/MLX42.h"

typedef struct s_app
{
	t_grid		*grid;
	t_camera	camera;
	t_renderer	renderer;
}				t_app;

t_app			*init_app(char *filename);
void			run_app(t_app *app);
void			free_app(t_app *app);

void			hook(void *param);

#endif

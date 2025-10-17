/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   app.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptison <ptison@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 20:45:19 by ptison            #+#    #+#             */
/*   Updated: 2025/10/18 00:59:36 by ptison           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



#ifndef APP_H
# define APP_H

# include "../lib/MLX42/include/MLX42/MLX42.h"
# include "../include/camera.h"
# include "../include/grid.h"
# include "../include/renderer.h"


typedef struct s_app {
    t_grid      *grid;
    t_camera     camera;
    t_renderer   renderer; 
} t_app;

t_app	*init_app(char *filename);
void	run_app(t_app *app);
void	free_app(t_app *app);

void	hook(void *param);
void	hook_project(void *param);
void	hook_rotate(void *param);
void	scrollhook(double xdelta, double ydelta, void *param);

t_point2d_temp	project_point(t_point3d point, t_camera *camera);

#endif
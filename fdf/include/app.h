/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   app.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptison <ptison@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/10 13:36:16 by ptison            #+#    #+#             */
/*   Updated: 2025/10/11 17:52:39 by ptison           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/map.h"
# include "../lib/MLX42/include/MLX42/MLX42.h"

typedef struct s_app
{
	mlx_t		*mlx;
	t_map		*map;
	mlx_image_t	*image;
}				t_app;

t_app	app_init(const char *file_name);
void	app_run(t_app app);
void	free_app(t_app app);
void	handle_input(void *param);
void	handle_close(void *param);
void	handle_resize(int32_t width, int32_t height, void *param);
void	render_map(t_app *app);

// Color conversion functions
uint32_t	rgb_to_mlx(uint32_t rgb_color);
uint32_t	rgba_to_mlx(uint32_t rgba_color);
uint32_t	create_mlx_color(uint8_t r, uint8_t g, uint8_t b, uint8_t a);

// Common colors
uint32_t	get_white(void);
uint32_t	get_black(void);
uint32_t	get_red(void);
uint32_t	get_green(void);
uint32_t	get_blue(void);
uint32_t	get_purple(void);

// Catppuccin palette (0-15)
uint32_t	get_catppuccin_0(void);
uint32_t	get_catppuccin_1(void);
uint32_t	get_catppuccin_2(void);
uint32_t	get_catppuccin_3(void);
uint32_t	get_catppuccin_4(void);
uint32_t	get_catppuccin_5(void);
uint32_t	get_catppuccin_6(void);
uint32_t	get_catppuccin_7(void);
uint32_t	get_catppuccin_8(void);
uint32_t	get_catppuccin_9(void);
uint32_t	get_catppuccin_10(void);
uint32_t	get_catppuccin_11(void);
uint32_t	get_catppuccin_12(void);
uint32_t	get_catppuccin_13(void);
uint32_t	get_catppuccin_14(void);
uint32_t	get_catppuccin_15(void);

// Catppuccin theme colors
uint32_t	get_catppuccin_background(void);
uint32_t	get_catppuccin_foreground(void);
uint32_t	get_catppuccin_cursor(void);
uint32_t	get_catppuccin_cursor_text(void);
uint32_t	get_catppuccin_selection_bg(void);
uint32_t	get_catppuccin_selection_fg(void);
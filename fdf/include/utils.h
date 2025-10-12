/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptison <ptison@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/12 19:04:53 by ptison            #+#    #+#             */
/*   Updated: 2025/10/12 19:05:54 by ptison           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include <stdint.h>

// Color conversion functions
uint32_t	rgb_to_mlx(uint32_t rgb_color);
uint32_t	rgba_to_mlx(uint32_t rgba_color);
uint32_t	create_mlx_color(uint8_t r, uint8_t g, uint8_t b, uint8_t a);

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

#endif

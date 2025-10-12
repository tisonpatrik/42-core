/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptison <ptison@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/11 17:24:35 by ptison            #+#    #+#             */
/*   Updated: 2025/10/12 20:12:38 by ptison           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


# include "../../include/utils.h"

/**
 * Creates MLX42 color from individual RGBA components
 * Handles Linux endianness bug by using ABGR format
 * 
 * @param r Red component (0-255)
 * @param g Green component (0-255)
 * @param b Blue component (0-255)
 * @param a Alpha component (0-255)
 * @return MLX42 compatible color
 */
uint32_t	create_mlx_color(uint8_t r, uint8_t g, uint8_t b, uint8_t a)
{
	return ((uint32_t)a << 24) | ((uint32_t)b << 16) | ((uint32_t)g << 8) | r;
}

/**
 * Converts RGB color (0xRRGGBB) to MLX42 format
 * Handles Linux endianness bug by using ABGR format
 * 
 * @param rgb_color RGB color in format 0xRRGGBB
 * @return MLX42 compatible color
 */
uint32_t	rgb_to_mlx(uint32_t rgb_color)
{
	uint8_t	r = (rgb_color >> 16) & 0xFF;  // Extract red
	uint8_t	g = (rgb_color >> 8) & 0xFF;   // Extract green  
	uint8_t	b = rgb_color & 0xFF;          // Extract blue
	uint8_t	a = 255;                       // Full alpha
	
	// Linux endianness fix: use ABGR format instead of RGBA
    return create_mlx_color(r, g, b, a);
}

/**
 * Converts RGBA color (0xRRGGBBAA) to MLX42 format
 * Handles Linux endianness bug by using ABGR format
 * 
 * @param rgba_color RGBA color in format 0xRRGGBBAA
 * @return MLX42 compatible color
 */
uint32_t	rgba_to_mlx(uint32_t rgba_color)
{
	uint8_t	r = (rgba_color >> 24) & 0xFF;  // Extract red
	uint8_t	g = (rgba_color >> 16) & 0xFF;  // Extract green
	uint8_t	b = (rgba_color >> 8) & 0xFF;   // Extract blue
	uint8_t	a = rgba_color & 0xFF;          // Extract alpha
	
	return create_mlx_color(r, g, b, a);
}

/**
 * Catppuccin color palette
 */
uint32_t	get_catppuccin_0(void)		{ return rgb_to_mlx(0x45475a); }  // Dark gray
uint32_t	get_catppuccin_1(void)		{ return rgb_to_mlx(0xf38ba8); }  // Pink
uint32_t	get_catppuccin_2(void)		{ return rgb_to_mlx(0xa6e3a1); }  // Green
uint32_t	get_catppuccin_3(void)		{ return rgb_to_mlx(0xf9e2af); }  // Yellow
uint32_t	get_catppuccin_4(void)		{ return rgb_to_mlx(0x89b4fa); }  // Blue
uint32_t	get_catppuccin_5(void)		{ return rgb_to_mlx(0xf5c2e7); }  // Pink
uint32_t	get_catppuccin_6(void)		{ return rgb_to_mlx(0x94e2d5); }  // Teal
uint32_t	get_catppuccin_7(void)		{ return rgb_to_mlx(0xa6adc8); }  // Light gray
uint32_t	get_catppuccin_8(void)		{ return rgb_to_mlx(0x585b70); }  // Darker gray
uint32_t	get_catppuccin_9(void)		{ return rgb_to_mlx(0xf38ba8); }  // Pink (same as 1)
uint32_t	get_catppuccin_10(void)	{ return rgb_to_mlx(0xa6e3a1); } // Green (same as 2)
uint32_t	get_catppuccin_11(void)	{ return rgb_to_mlx(0xf9e2af); } // Yellow (same as 3)
uint32_t	get_catppuccin_12(void)	{ return rgb_to_mlx(0x89b4fa); } // Blue (same as 4)
uint32_t	get_catppuccin_13(void)	{ return rgb_to_mlx(0xf5c2e7); } // Pink (same as 5)
uint32_t	get_catppuccin_14(void)	{ return rgb_to_mlx(0x94e2d5); } // Teal (same as 6)
uint32_t	get_catppuccin_15(void)	{ return rgb_to_mlx(0xbac2de); } // Light blue-gray

/**
 * Catppuccin theme colors
 */
uint32_t	get_catppuccin_background(void)		{ return rgb_to_mlx(0x1e1e2e); } // Dark background
uint32_t	get_catppuccin_foreground(void)		{ return rgb_to_mlx(0xcdd6f4); } // Light foreground
uint32_t	get_catppuccin_cursor(void)			{ return rgb_to_mlx(0xf5e0dc); } // Cursor color
uint32_t	get_catppuccin_cursor_text(void)		{ return rgb_to_mlx(0x11111b); } // Cursor text
uint32_t	get_catppuccin_selection_bg(void)	{ return rgb_to_mlx(0x353749); } // Selection background
uint32_t	get_catppuccin_selection_fg(void)	{ return rgb_to_mlx(0xcdd6f4); } // Selection foreground
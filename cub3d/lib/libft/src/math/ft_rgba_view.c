/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_rgba_view.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptison <ptison@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/10 13:41:14 by ptison            #+#    #+#             */
/*   Updated: 2026/08/10 13:41:15 by ptison           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "color.h"

t_rgba_view	ft_rgba_view(uint8_t *bytes, size_t width, size_t height,
	size_t stride)
{
	return ((t_rgba_view){bytes, width, height, stride});
}

bool	ft_rgba_view_contains(const t_rgba_view *view, int x, int y)
{
	return (view && view->bytes && x >= 0 && y >= 0
		&& (size_t)x < view->width && (size_t)y < view->height);
}

t_rgba_ref	ft_rgba_view_pixel(const t_rgba_view *view, int x, int y)
{
	return ((t_rgba_ref){view->bytes + (size_t)y * view->stride
		+ (size_t)x * FT_RGBA_CHANNEL_COUNT});
}

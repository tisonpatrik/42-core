/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_rgba_blend.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptison <ptison@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/10 13:41:10 by ptison            #+#    #+#             */
/*   Updated: 2026/08/10 13:41:11 by ptison           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "color.h"

static uint8_t	source_over_channel(uint8_t source, uint8_t destination,
	unsigned int source_alpha, unsigned int output_alpha)
{
	unsigned int	color;
	unsigned int	destination_weight;

	if (output_alpha == 0)
		return (0);
	color = source * source_alpha * FT_COLOR_CHANNEL_MAX;
	destination_weight = output_alpha
		- source_alpha * FT_COLOR_CHANNEL_MAX;
	color += destination * destination_weight;
	return ((uint8_t)(color / output_alpha));
}

static uint8_t	source_over_opaque(uint8_t source, uint8_t destination,
	unsigned int source_alpha)
{
	unsigned int	inverse_alpha;

	inverse_alpha = FT_COLOR_CHANNEL_MAX - source_alpha;
	return ((uint8_t)((source * source_alpha + destination * inverse_alpha)
		/ FT_COLOR_CHANNEL_MAX));
}

t_rgba	ft_rgba_source_over(t_rgba source, t_rgba destination)
{
	unsigned int	output_alpha;
	t_rgba			result;

	if (source.alpha == FT_COLOR_CHANNEL_MAX)
		return (source);
	if (source.alpha == 0)
		return (destination);
	if (destination.alpha == FT_COLOR_CHANNEL_MAX)
		return ((t_rgba){
			source_over_opaque(source.red, destination.red, source.alpha),
			source_over_opaque(source.green, destination.green, source.alpha),
			source_over_opaque(source.blue, destination.blue, source.alpha),
			FT_COLOR_CHANNEL_MAX});
	output_alpha = source.alpha * FT_COLOR_CHANNEL_MAX;
	output_alpha += (unsigned int)destination.alpha
		* (FT_COLOR_CHANNEL_MAX - source.alpha);
	result.red = source_over_channel(source.red, destination.red,
			source.alpha, output_alpha);
	result.green = source_over_channel(source.green, destination.green,
			source.alpha, output_alpha);
	result.blue = source_over_channel(source.blue, destination.blue,
			source.alpha, output_alpha);
	result.alpha = (uint8_t)(output_alpha / FT_COLOR_CHANNEL_MAX);
	return (result);
}

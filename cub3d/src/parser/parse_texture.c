/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_texture.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jakrajic <jakrajic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/06 18:16:08 by jakrajic          #+#    #+#             */
/*   Updated: 2026/08/06 18:16:17 by jakrajic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int	parse_texture(char *line, char **path, char c)
{
	while (*line && is_in(*line, SPACE))
		line++;
	if (*line == '\t')
		return (display_error("Tabs are not allowed! in textures!"), 1);
	if (*path != NULL)
	{
		if (c == 'n')
			display_error("NO texture path duplicate found!");
		else if (c == 's')
			display_error("SO texture path duplicate found!");
		else if (c == 'w')
			display_error("WE texture path duplicate found!");
		else if (c == 'e')
			display_error("EA texture path duplicate found!");
		return (1);
	}
	erase_white_eof(line, WHITE);
	if (!*line)
		return (display_error("Missing texture path!"), 1);
	*path = ft_strdup(line);
	if (!*path)
		return (display_error("Memory allocation failed for texture path!"), 1);
	return (0);
}

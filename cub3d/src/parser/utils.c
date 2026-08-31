/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jakrajic <jakrajic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/06 18:16:22 by jakrajic          #+#    #+#             */
/*   Updated: 2026/08/06 19:09:42 by jakrajic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int	is_in(char c, char *set)
{
	if (!set || c == '\0')
		return (0);
	return (ft_strchr(set, c) != NULL);
}

int	empty_line(char *line)
{
	if (!line)
		return (0);
	while (*line)
	{
		if (!is_in(*line, WHITE))
			return (0);
		line++;
	}
	return (1);
}

void	erase_white_eof(char *line, char *macro_type)
{
	int	len;

	if (!line || !*line)
		return ;
	len = ft_strlen(line);
	while (len > 0 && is_in(line[len - 1], macro_type))
	{
		line[len - 1] = '\0';
		len--;
	}
}

int	is_map_line(char *line)
{
	int	i;

	i = 0;
	while (line[i] && !is_in(line [i], EOFCHARS))
	{
		if (!is_in(line[i], MAPCHARS))
			return (0);
		i++;
	}
	return (1);
}

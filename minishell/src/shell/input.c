/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omaly <student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/26 12:39:06 by omaly             #+#    #+#             */
/*   Updated: 2026/02/26 12:39:10 by omaly            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*shell_get_input(void)
{
	char	*line;
	char	*newline_pos;

	if (isatty(STDIN_FILENO))
		return (readline("minishell$ "));
	line = ft_get_line(STDIN_FILENO);
	if (!line)
		return (NULL);
	newline_pos = ft_strchr(line, '\n');
	if (newline_pos)
		*newline_pos = '\0';
	return (line);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptison <ptison@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/27 16:40:00 by ptison            #+#    #+#             */
/*   Updated: 2025/10/11 17:53:33 by ptison           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/map.h"

int	get_file_fd(const char *file_name)
{
	int	fd;

	fd = open(file_name, O_RDONLY);
	if (fd < 0)
	{
		perror("open");
		return (-1);
	}
	return (fd);
}

int	count_tokens(char **tokens)
{
	int	count;

	count = 0;
	while (tokens[count])
		count++;
	return (count);
}

int	parse_token(const char *token)
{
	char	*endptr;
	int		value;

	if (!token || token[0] == '\0')
		return (-1);
	errno = 0;
	value = ft_strtoi10(token, &endptr);
	if (*endptr != '\0' || errno == ERANGE)
		return (-1);
	return (value);
}

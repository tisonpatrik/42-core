/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptison <ptison@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/27 11:37:00 by ptison            #+#    #+#             */
/*   Updated: 2025/09/27 11:37:43 by ptison           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"
#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int	get_file_descriptor(char *file_name)
{
	int	fd;

	fd = open(file_name, O_RDONLY);
	if (fd < 0)
	{
		perror("open");
		exit(EXIT_FAILURE);
	}
	return (fd);
}

void	fatal_cleanup_and_exit(int *buf, char **tmp)
{
	if (buf)
		free(buf);
	if (tmp)
		ft_free_array(tmp);
	exit(EXIT_FAILURE);
}

void	store_token(const char *tok, int *out, int *out_index,
		char **parts_for_cleanup)
{
	char	*endptr;
	int		val;

	endptr = NULL;
	if (!tok || tok[0] == '\0')
		fatal_cleanup_and_exit(out, parts_for_cleanup);
	errno = 0;
	val = ft_strtoi10(tok, &endptr);
	if (*endptr != '\0' || errno == ERANGE)
		fatal_cleanup_and_exit(out, parts_for_cleanup);
	out[(*out_index)++] = val;
}

void	fill_from_parts(char **parts, int *out)
{
	int	j;
	int	out_index;

	out_index = 0;
	j = 0;
	if (!parts)
		fatal_cleanup_and_exit(out, NULL);
	while (parts[j])
	{
		store_token(parts[j], out, &out_index, parts);
		j++;
	}
	ft_free_array(parts);
}

int	get_count_parts(char **parts)
{
	int	j;
	int	count;

	j = 0;
	count = 0;
	while (parts[j])
	{
		if (parts[j][0] == '\0')
			fatal_cleanup_and_exit(NULL, parts);
		count++;
		j++;
	}
	return (count);
}

void	get_map(char *file_name)
{
	int		fd;
	char	*text_line;
		char trim_chars[] = {CHAR_CARRIAGE_RETURN, CHAR_NEWLINE, CHAR_NULL};
	char	*trimmed_line;
	char	**set;
	int		total;
	int		*line;

	fd = get_file_descriptor(file_name);
	while ((text_line = ft_get_line(fd)) != NULL)
	{
		// Trim \r\n from end to prevent empty tokens
		trimmed_line = ft_strtrim(text_line, trim_chars);
		free(text_line);
		if (!trimmed_line)
			fatal_cleanup_and_exit(NULL, NULL);
		set = ft_split(trimmed_line, CHAR_SPACE);
		free(trimmed_line);
		if (!set)
			fatal_cleanup_and_exit(NULL, NULL);
		total = get_count_parts(set);
		line = (int *)malloc(sizeof(int) * total);
		if (!line)
			fatal_cleanup_and_exit(NULL, set);
		fill_from_parts(set, line);
		free(line);
	}
	close(fd);
}
int	main(int argc, char **argv)
{
	if (argc != 2)
	{
		return (EXIT_FAILURE);
	}
	get_map(argv[1]);
	return (EXIT_SUCCESS);
}

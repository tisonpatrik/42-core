/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_reader.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptison <ptison@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/27 12:52:19 by ptison            #+#    #+#             */
/*   Updated: 2025/09/27 13:06:29 by ptison           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



#include "../../include/map.h"


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
static void parse_token_or_die(const char *tok, t_cell *out,
                               int *line_to_free, char **parts_for_cleanup)
{
    if (!tok || tok[0] == '\0')
        fatal_cleanup_and_exit(line_to_free, parts_for_cleanup);

    errno = 0;
    char *endp = NULL;
    int z = ft_strtoi10(tok, &endp);
    if (errno == ERANGE || endp == tok)
        fatal_cleanup_and_exit(line_to_free, parts_for_cleanup);

    out->z = (int)z;
    out->has_color = 0;
    out->color = 0;

    if (*endp == ',') {
        const char *c = endp + 1;
        if (c[0] == '0' && (c[1] == 'x' || c[1] == 'X'))
            c += 2;

        errno = 0;
        char *endc = NULL;
        int col = ft_strtoi10(c, &endc);
        if (errno == ERANGE || c == endc || *endc != '\0' || col < 0 || col > 0xFFFFFF)
            fatal_cleanup_and_exit(line_to_free, parts_for_cleanup);

        out->has_color = 1;
        out->color = (uint32_t)col;
    } else if (*endp != '\0') {
        fatal_cleanup_and_exit(line_to_free, parts_for_cleanup);
    }
}

static void fill_cells_from_parts(char **parts, t_cell *out_cells, int count)
{
    if (!parts)
        fatal_cleanup_and_exit(NULL, NULL);

    for (int j = 0; j < count; j++)
        parse_token_or_die(parts[j], &out_cells[j], NULL, parts);
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

t_map read_map(const char *file_name)
{
    t_map m;
    map_init(&m);

    int   fd = get_file_descriptor((char*)file_name);
    char *text_line = NULL;

    char trim_chars[] = {CHAR_CARRIAGE_RETURN, CHAR_NEWLINE, CHAR_NULL};

    while ((text_line = ft_get_line(fd)) != NULL)
    {
        char *trimmed = ft_strtrim(text_line, trim_chars);
        free(text_line); text_line = NULL;
        if (!trimmed) { map_free(&m); fatal_cleanup_and_exit(NULL, NULL); }

        if (trimmed[0] == '\0') { free(trimmed); continue; }

        char **parts = ft_split(trimmed, CHAR_SPACE);
        free(trimmed);
        if (!parts) { map_free(&m); fatal_cleanup_and_exit(NULL, NULL); }

        int total = get_count_parts(parts);
        t_cell *cells = (t_cell *)malloc(sizeof(t_cell) * total);
        if (!cells) { ft_free_array(parts); map_free(&m); fatal_cleanup_and_exit(NULL, NULL); }

        fill_cells_from_parts(parts, cells, total);
        ft_free_array(parts);

        map_push_row(&m, cells, total);
    }

    close(fd);
    if (m.nrows == 0) {
        fprintf(stderr, "Empty map\n");
        exit(EXIT_FAILURE);
    }
    return m;
}



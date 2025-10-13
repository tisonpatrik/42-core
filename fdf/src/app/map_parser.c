

# include "../../include/app.h"

int	hex_to_int(const char *hex_str)
{
	int	result;
	int	i;

	result = 0;
	i = 0;
	while (hex_str[i])
	{
		result *= 16;
		if (hex_str[i] >= '0' && hex_str[i] <= '9')
			result += hex_str[i] - '0';
		else if (hex_str[i] >= 'A' && hex_str[i] <= 'F')
			result += hex_str[i] - 'A' + 10;
		else if (hex_str[i] >= 'a' && hex_str[i] <= 'f')
			result += hex_str[i] - 'a' + 10;
		i++;
	}
	return (result);
}

int	parse_color(int fd, t_view *map, char *tabj)
{
	while (*tabj == '-')
		tabj++;
	while (ft_isdigit(*tabj))
		tabj++;
	if (*tabj == ',')
		tabj++;
	else
		return (0xFFFFFFFF);
	if ((ft_strncmp(tabj, "0X", 2) && ft_strncmp(tabj, "0x", 2)))
		error_map(fd, map, INVALID_MAP);
	tabj += 2;
	ft_striteri(tabj, &make_upper);
	return ((hex_to_int(tabj) << 8) | 0xFF);
}

void	parse_column(int fd, t_view *map, char **tab, int i)
{
	t_point3d	*point;
	int			x_offset;
	int			y_offset;
	int			j;

	j = -1;
	while (++j < map->grid_info.cols)
	{
		if (!ft_isdigit(*tab[j]) && *tab[j] != '-')
			error_map(fd, map, INVALID_MAP);
		point = &(map->grid.grid3d[i][j]);
		x_offset = (map->grid_info.cols - 1) * map->camera.interval / 2;
		y_offset = (map->grid_info.rows - 1) * map->camera.interval / 2;
		point->x = (double)j * (map->camera.interval) - x_offset;
		point->y = (double)i * (map->camera.interval) - y_offset;
		point->z = (double)ft_atoi(tab[j]) * (map->camera.interval);
		map->grid_info.high = ft_max(map->grid_info.high, point->z);
		map->grid_info.low = ft_min(map->grid_info.low, point->z);
		point->mapcolor = parse_color(fd, map, tab[j]);
	}
}

void	parse_map(int fd, t_view *map)
{
	char	*line;
	char	*temp;
	char	**tab;
	int		i;

	i = -1;
	while (++i < map->grid_info.rows)
	{
		temp = ft_get_line(fd);
		if (!temp)
			error_map(fd, map, MALLOC);
		line = ft_strtrim(temp, "\n");
		free(temp);
		if (!line)
			error_map(fd, map, MALLOC);
		tab = ft_split(line, ' ');
		free(line);
		if (!tab)
			error_map(fd, map, MALLOC);
		parse_column(fd, map, tab, i);
		ft_free_tab((void **)tab, map->grid_info.cols);
	}
}

int	get_cols(int fd, t_view *map, char *line)
{
	char	**tab;
	char	*temp;
	int		i;

	temp = ft_strtrim(line, "\n");
	free(line);
	if (!temp)
		error_map(fd, map, MALLOC);
	tab = ft_split(temp, ' ');
	free(temp);
	if (!tab)
		error_map(fd, map, MALLOC);
	i = 0;
	while (tab[i])
	{
		map->grid_info.high = ft_max(map->grid_info.high, ft_atoi(tab[i]));
		map->grid_info.low = ft_min(map->grid_info.low, ft_atoi(tab[i]));
		i++;
	}
	ft_free_tab((void **)tab, i);
	return (i);
}

void	get_dimensions(int fd, t_view *map)
{
	char	*line;

	line = ft_get_line(fd);
	if (!line)
		error_map(fd, map, MALLOC);
	map->grid_info.cols = get_cols(fd, map, line);
	if (map->grid_info.cols == 0)
		error_map(fd, map, INVALID_MAP);
	map->grid_info.rows = 1;
	while (1)
	{
		line = ft_get_line(fd);
		if (!line)
			break ;
		map->grid_info.rows++;
		if (map->grid_info.cols != get_cols(fd, map, line))
			error_map(fd, map, INVALID_MAP);
	}
}

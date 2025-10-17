
# include "../../include/grid.h"

static uint32_t	parse_color_to_mlx42(const char *color_str)
{
	uint32_t rgb_color;

	if (!color_str)
		return (0xFF45475A);
	
	if (ft_strncmp(color_str, "0x", 2) == 0 || ft_strncmp(color_str, "0X", 2) == 0)
		rgb_color = hex_to_int(color_str + 2);
	else
		rgb_color = hex_to_int(color_str);
	
	return ((0xFF << 24) | rgb_color);
}

static t_token_data	parse_token_with_color(const char *token, char *comma_pos)
{
	t_token_data	data;
	char			*z_str;
	char			*color_str;

	data.z_value = 0;
	data.color = 0xFF45475A;
	
	z_str = ft_substr(token, 0, comma_pos - token);
	color_str = ft_strdup(comma_pos + 1);
	
	if (z_str)
	{
		data.z_value = ft_atoi(z_str);
		free(z_str);
	}
	if (color_str)
	{
		data.color = parse_color_to_mlx42(color_str);
		free(color_str);
	}
	
	return (data);
}
static double	calculate_grid_interval(size_t rows, size_t cols, int width, int height)
{
	double	interval;

	interval = ft_min(width / cols, height / rows) / 2.0;
	return (ft_max(2, interval));
}
t_token_data	parse_token(const char *token)
{
	t_token_data	data;
	char			*comma_pos;

	data.z_value = 0;
	data.color = 0xFF45475A;
	
	if (!token || token[0] == '\0')
	{
		data.z_value = -1;
		return (data);
	}
	
	comma_pos = ft_strchr(token, ',');
	if (comma_pos)
		data = parse_token_with_color(token, comma_pos);
	else
		data.z_value = ft_atoi(token);
	
	return (data);
}

bool	parse_grid_row(char **tokens, t_grid *grid, int row_index, int width, int height)
{
	t_token_data	data;
	t_point3d		*point;
	int				col_index;
	double			interval;
	int				x_offset;
	int				y_offset;

	interval = calculate_grid_interval(grid->rows, grid->cols, width, height);
	x_offset = (grid->cols - 1) * interval / 2;
	y_offset = (grid->rows - 1) * interval / 2;
	
	col_index = 0;
	while (tokens[col_index] && col_index < grid->cols)
	{
		data = parse_token(tokens[col_index]);
		if (data.z_value == -1)
			return (false);
		
		point = &(grid->grid3d[row_index][col_index]);
		point->x = (double)col_index * interval - x_offset;
		point->y = (double)row_index * interval - y_offset;
		point->z = (double)data.z_value * interval;
		point->mapcolor = data.color;
		
		grid->high = ft_max(grid->high, point->z);
		grid->low = ft_min(grid->low, point->z);
		
		col_index++;
	}
	
	while (col_index < grid->cols)
	{
		point = &(grid->grid3d[row_index][col_index]);
		point->x = (double)col_index * interval - x_offset;
		point->y = (double)row_index * interval - y_offset;
		point->z = 0.0;
		point->mapcolor = 0xFFFFFFFF;
		col_index++;
	}
	
	return (true);
}

t_grid_info	analyze_grid_file(const char *filename)
{
	t_grid_info	info;
	char		*line;
	char		**tokens;
	int			fd;

	info.rows = 0;
	info.cols = 0;
	info.fd = -1;
	
	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (info);
	
	info.fd = fd;
	
	while ((line = ft_get_line(fd)) != NULL)
	{
		tokens = ft_split(line, ' ');
		free(line);
		
		if (tokens)
		{
			info.cols = ft_max(info.cols, count_tokens(tokens));
			ft_free_array(tokens);
		}
		info.rows++;
	}
	
	close(fd);
	info.fd = open(filename, O_RDONLY);
	return (info);
}


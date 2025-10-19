/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   row_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptison <ptison@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/19 21:22:48 by ptison            #+#    #+#             */
/*   Updated: 2025/10/19 21:41:57 by ptison           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/grid.h"

static void	set_point_from_token(t_point3d *point, t_token_data *data,
		int row_index, int col_index, t_grid_info *info)
{
	point->x = (double)col_index * info->interval - info->x_offset;
	point->y = (double)row_index * info->interval - info->y_offset;
	point->z = (double)data->z_value * info->interval;
	point->mapcolor = data->color;
}

static void	set_point_default(t_point3d *point, int row_index, int col_index,
		t_grid_info *info)
{
	point->x = (double)col_index * info->interval - info->x_offset;
	point->y = (double)row_index * info->interval - info->y_offset;
	point->z = 0.0;
	point->mapcolor = 0xFFFFFFFF;
}

static int	process_row_tokens(char **tokens, t_grid *grid, int row_index,
		t_grid_info *info)
{
	t_token_data	data;
	t_point3d		*point;
	int				col_index;

	col_index = 0;
	while (tokens[col_index] && col_index < grid->cols)
	{
		data = parse_token(tokens[col_index]);
		if (data.z_value == -1)
			return (-1);
		point = &(grid->grid3d[row_index][col_index]);
		set_point_from_token(point, &data, row_index, col_index, info);
		grid->high = ft_max(grid->high, point->z);
		grid->low = ft_min(grid->low, point->z);
		col_index++;
	}
	return (col_index);
}

static void	fill_remaining_columns(t_grid *grid, int row_index, int start_col,
		t_grid_info *info)
{
	t_point3d	*point;
	int			col_index;

	col_index = start_col;
	while (col_index < grid->cols)
	{
		point = &(grid->grid3d[row_index][col_index]);
		set_point_default(point, row_index, col_index, info);
		col_index++;
	}
}

bool	parse_grid_row(char **tokens, t_grid *grid, int row_index,
		t_grid_info *info)
{
	int	processed_tokens;

	processed_tokens = process_row_tokens(tokens, grid, row_index, info);
	if (processed_tokens == -1)
		return (false);
	if (processed_tokens < grid->cols)
		fill_remaining_columns(grid, row_index, processed_tokens, info);
	return (true);
}

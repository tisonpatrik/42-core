/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_orchestrator.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptison <ptison@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 23:25:35 by ptison            #+#    #+#             */
/*   Updated: 2025/10/13 23:25:37 by ptison           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../include/app.h"

/* ========================================================================== */
/* HIGH-LEVEL PARSING FUNCTIONS - Orchestrate the process                   */
/* ========================================================================== */

int	parse_map_from_lines(char **lines, int line_count, t_view *view)
{
	char	**tokens;
	int		row;

	row = 0;
	while (row < line_count)
	{
		tokens = ft_split(lines[row], ' ');
		if (!tokens)
			return (0);
		
		build_column_from_tokens(tokens, &view->grid, &view->camera, row);
		ft_free_tab((void **)tokens, view->grid.cols);
		row++;
	}
	return (1);
}

int	get_map_dimensions(char **lines, int line_count, t_view *view)
{
	int	cols;
	int	row;

	if (line_count == 0)
		return (0);
	
	cols = get_column_count(lines[0]);
	if (cols == 0)
		return (0);
	
	view->grid.cols = cols;
	view->grid.rows = line_count;
	
	/* Validate all lines have same column count */
	row = 1;
	while (row < line_count)
	{
		if (get_column_count(lines[row]) != cols)
			return (0);
		row++;
	}
	return (1);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   experimental.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptison <ptison@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 22:14:50 by ptison            #+#    #+#             */
/*   Updated: 2025/10/17 20:37:57 by ptison           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPERIMENTAL_H
# define EXPERIMENTAL_H

# include "../include/old_app.h"
# include "../include/heightmap.h"

t_grid	*allocate_grid(int rows, int cols);
t_grid	*get_grid(t_heightmap *heightmap);
void	free_grid(t_view *view);
#endif
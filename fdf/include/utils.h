/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptison <ptison@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 23:54:55 by ptison            #+#    #+#             */
/*   Updated: 2025/10/24 18:18:36 by ptison           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include "../lib/MLX42/include/MLX42/MLX42.h"
# include "../lib/libft/include/libft.h"
# include <errno.h>
# include <stdio.h>
# include <stdlib.h>

int		hex_to_int(const char *hex_str);
void	fdf_error(const char *message);

void	handle_error(char *message);
#endif

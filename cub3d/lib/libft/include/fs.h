/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fs.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptison <ptison@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/10 13:36:59 by ptison            #+#    #+#             */
/*   Updated: 2026/08/10 13:36:59 by ptison           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FS_H
# define FS_H

# include "allocator.h"
# include "str8.h"

bool	ft_read_file(t_arena *arena, const char *filepath, t_str8 *file);

#endif

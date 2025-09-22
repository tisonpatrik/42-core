/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   snapshot_arena.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptison <ptison@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 21:13:05 by ptison            #+#    #+#             */
/*   Updated: 2025/09/22 18:28:06 by ptison           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SNAPSHOT_ARENA_H
# define SNAPSHOT_ARENA_H

# include "../libft/include/libft.h"
# include "stack.h"
# include <stdbool.h>
# include <stdlib.h>

typedef struct s_snapshot_arena
{
	int				*a_values;
	int				*b_values;
	int				size_a;
	int				size_b;
}					t_snapshot_arena;

t_snapshot_arena	*create_snapshot_arena(void);
void				destroy_snapshot_arena(t_snapshot_arena *arena);

bool				take_snapshots(t_snapshot_arena *arena, t_stack *stack_a,
						t_stack *stack_b);
#endif

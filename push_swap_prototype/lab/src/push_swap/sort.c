/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: patrik <patrik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 21:08:28 by ugerkens          #+#    #+#             */
/*   Updated: 2025/08/25 10:55:02 by patrik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/push_swap.h"
#include "../../include/debug_logging.h"

void	sort(t_ps *data)
{
	chunk_sort(data);
	
	post_sort_optimization(data);
	
	debug_log(DEBUG_DEBUG, "=== SORT END ===");
}

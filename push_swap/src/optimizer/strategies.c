/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strategies.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: patrik <patrik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/19 20:48:46 by ptison            #+#    #+#             */
/*   Updated: 2025/09/19 22:12:32 by patrik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/optimizer.h"

#define MAX_STRATEGIES 10

typedef struct s_strategy_registry
{
	t_optimization_strategy	*strategies[MAX_STRATEGIES];
	int						count;
}							t_strategy_registry;

static t_strategy_registry	*g_registry = NULL;

void	free_strategy_registry(void)
{
	if (g_registry)
	{
		free(g_registry);
		g_registry = NULL;
	}
}

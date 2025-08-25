/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_mngt.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: patrik <patrik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 21:08:35 by ugerkens          #+#    #+#             */
/*   Updated: 2025/08/25 00:43:57 by patrik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/stack.h"
#include "../../include/debug_logging.h"

void	init_data(t_ps *data, int argc, char **argv, bool writing_mode)
{
	// Debug: Log function entry
	debug_log(DEBUG_DEBUG, "=== INIT_DATA START ===");
	debug_log(DEBUG_DEBUG, "Arguments count: %d, Writing mode: %s", argc, writing_mode ? "true" : "false");
	
	--argc;
	debug_log(DEBUG_DEBUG, "After --argc: argc = %d", argc);
	
	debug_log(DEBUG_DEBUG, "Calling init_stack for stack A");
	init_stack(data, &data->a, argc);
	
	debug_log(DEBUG_DEBUG, "Calling init_stack for stack B");
	init_stack(data, &data->b, argc);
	
	debug_log(DEBUG_DEBUG, "Calling fill_stack for stack A");
	fill_stack(data, &data->a, argc, ++argv);
	
	data->writing_mode = writing_mode;
	data->op_list = NULL;
	
	debug_log(DEBUG_DEBUG, "=== INIT_DATA END ===");
}

void	init_stack(t_ps *data, t_stack *stk, int size)
{
	// Debug: Log function entry
	debug_log(DEBUG_DEBUG, "=== INIT_STACK START ===");
	debug_log(DEBUG_DEBUG, "Size: %d", size);
	
	stk->stack = malloc(sizeof(int) * size);
	if (!stk->stack)
		error(data);
	
	debug_log(DEBUG_DEBUG, "Allocated stack array");
	
	stk->top = 0;
	stk->bottom = 0;
	stk->size = size;
	
	debug_log(DEBUG_DEBUG, "Set stk->top=%d, stk->bottom=%d, stk->size=%d", stk->top, stk->bottom, stk->size);
	
	ft_memset(stk->stack, 0, sizeof(int) * size);
	debug_log(DEBUG_DEBUG, "Initialized stack array with zeros");
	
	debug_log(DEBUG_DEBUG, "=== INIT_STACK END ===");
}

bool	is_sorted(t_ps *data)
{
	int	i;
	int	rank;

	// Debug: Log function entry
	debug_log(DEBUG_DEBUG, "=== IS_SORTED START ===");
	debug_log(DEBUG_DEBUG, "Stack A size: %d", data->a.size);
	
	i = data->a.top;
	rank = 1;
	
	debug_log(DEBUG_DEBUG, "Starting check from top=%d, expected rank=1", i);
	
	while (rank <= data->a.size)
	{
		debug_log(DEBUG_DEBUG, "Checking position %d: expected rank=%d, actual value=%d", i, rank, data->a.stack[i]);
		
		if (data->a.stack[i] != rank)
		{
			debug_log(DEBUG_DEBUG, "NOT SORTED: position %d has value %d, expected %d", i, data->a.stack[i], rank);
			return (false);
		}
		rank++;
		i = next_down(&data->a, i);
	}
	
	debug_log(DEBUG_DEBUG, "Stack A is SORTED");
	debug_log(DEBUG_DEBUG, "=== IS_SORTED END ===");
	return (true);
}

void	error(t_ps *data)
{
	free_data(data);
	ft_putendl_fd("Error", 2);
	exit(EXIT_FAILURE);
}

void	free_data(t_ps *data)
{
	if (data->a.stack)
		free(data->a.stack);
	if (data->b.stack)
		free(data->b.stack);
	if (data->op_list)
		ft_lstclear(&data->op_list, NULL);
}

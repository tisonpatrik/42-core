/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugerkens <ugerkens@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 21:08:24 by ugerkens          #+#    #+#             */
/*   Updated: 2023/07/27 21:08:26 by ugerkens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/push_swap.h"
#include "../include/debug_logging.h"

int	main(int argc, char *argv[])
{
	t_ps	data;

	// Initialize debug logging with maximum detail
	debug_init("logs", DEBUG_TRACE);
	
	init_data(&data, argc, argv, true);
	
	// Log initial state
	debug_log(DEBUG_INFO, "Starting push_swap with %d arguments", argc);
	debug_log_stack_state(&data, "after initialization");
	
	sort(&data);
	
	// Log final state
	debug_log(DEBUG_INFO, "Sorting completed");
	debug_log_stack_state(&data, "after sorting");
	
	print_operations(data.op_list);
	
	// Cleanup debug logging
	debug_cleanup();
	
	free_data(&data);
	exit(EXIT_SUCCESS);
}

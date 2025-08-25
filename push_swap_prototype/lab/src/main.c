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
	
	// Debug: Log main function entry
	debug_log(DEBUG_DEBUG, "=== MAIN START ===");
	debug_log(DEBUG_DEBUG, "Arguments count: %d", argc);
	
	init_data(&data, argc, argv, true);
	
	// Log initial state
	debug_log(DEBUG_INFO, "Starting push_swap with %d arguments", argc);
	debug_log_stack_state(&data, "after initialization");
	
	// Debug: Log before calling sort
	debug_log(DEBUG_DEBUG, "Calling sort(&data)");
	sort(&data);
	
	// Log final state
	debug_log(DEBUG_INFO, "Sorting completed");
	debug_log_stack_state(&data, "after sorting");
	
	// Debug: Log before printing operations
	debug_log(DEBUG_DEBUG, "Calling print_operations");
	print_operations(data.op_list);
	
	// Cleanup debug logging
	debug_log(DEBUG_DEBUG, "Calling debug_cleanup");
	debug_cleanup();
	
	debug_log(DEBUG_DEBUG, "Calling free_data");
	free_data(&data);
	
	debug_log(DEBUG_DEBUG, "=== MAIN END ===");
	exit(EXIT_SUCCESS);
}

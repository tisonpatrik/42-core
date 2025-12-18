/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptison <ptison@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/18 13:52:58 by ptison            #+#    #+#             */
/*   Updated: 2025/12/18 13:58:58 by ptison           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIMULATION_H
# define SIMULATION_H

# include "philosophy.h"
# include "table.h"
# include "validation.h"
# include <stdio.h>
# include <stdlib.h>

typedef struct s_simulation
{
	t_table			table;
	t_philosopher	**philos;
	pthread_t		grim_reaper;
}					t_simulation;

typedef struct s_result
{
	t_simulation	*simulation;
	bool			ok;
}					t_result;

void				sim_start_delay(time_t start_time);
void				*grim_reaper(void *data);
t_result			create_simulation(t_inputs inputs);
void				destroy_simulation(t_simulation *sim);
char				*start_simulation(t_simulation *sim);
void				stop_simulation(t_simulation *sim);
time_t				get_time_in_ms(void);
bool				has_simulation_stopped(t_table *table);
void				sim_start_delay(time_t start_time);
pthread_mutex_t		*init_forks(unsigned int count);
void				destroy_forks(pthread_mutex_t *forks, unsigned int count);
#endif

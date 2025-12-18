/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophy.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptison <ptison@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/18 13:53:08 by ptison            #+#    #+#             */
/*   Updated: 2025/12/18 13:53:15 by ptison           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHY_H
# define PHILOSOPHY_H

# include "table.h"
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

typedef struct s_philosopher
{
	pthread_t		thread;
	unsigned int	id;

	unsigned int	times_ate;
	time_t			last_meal;
	pthread_mutex_t	meal_time_lock;

	unsigned int	fork_left;
	unsigned int	fork_right;

	t_table			*table;
}					t_philosopher;

void				write_status(t_philosopher *philo, char *status);
void				precise_sleep(t_table *table, time_t duration);
void				take_forks(t_philosopher *philo);
void				drop_forks(t_philosopher *philo);

void				do_eating(t_philosopher *philo);
void				do_sleeping(t_philosopher *philo);
void				do_thinking(t_philosopher *philo);

t_philosopher		**init_philosophers(t_table *table);
void				destroy_philosophers(t_philosopher **philos,
						unsigned int count);
void				*do_philosophy(void *data);
#endif

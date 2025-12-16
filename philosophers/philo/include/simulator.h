#ifndef SIMULATOR_H
#define SIMULATOR_H

# include <pthread.h>
# include <limits.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <stdbool.h>

#include "validation.h"

typedef struct s_philo	t_philosopher;


typedef struct s_simulation
{
	time_t			start_time;
	unsigned int	nb_philos;
	pthread_t		grim_reaper;
	time_t			time_to_die;
	time_t			time_to_eat;
	time_t			time_to_sleep;
	int				must_eat_count;
	bool			sim_stop;
	pthread_mutex_t	sim_stop_lock;
	pthread_mutex_t	write_lock;
	pthread_mutex_t	*fork_locks;
	t_philosopher			**philosophers;
}	t_simulation;

typedef struct s_result
{
	t_simulation	*simulation;
	bool			ok;
}	t_result;

typedef struct s_philo
{
	pthread_t			thread;
	unsigned int		id;
	unsigned int		times_ate;

	unsigned int        left_fork;
	unsigned int        right_fork;
	pthread_mutex_t		meal_time_lock;
	time_t				last_meal;
	t_simulation				*simulation;
}	t_philosopher;

typedef enum e_status
{
	DIED = 0,
	EATING = 1,
	SLEEPING = 2,
	THINKING = 3,
	GOT_FORK_1 = 4,
	GOT_FORK_2 = 5
}	t_status;

char	*start_simulation(t_simulation *simulation);
void	stop_simulation(t_simulation	*table);


t_result				create_simulation(t_inputs inputs);
time_t			get_time_in_ms(void);
void			philo_sleep(t_simulation *table, time_t sleep_time);
void			sim_start_delay(time_t start_time);


void			*grim_reaper(void *data);
bool			has_simulation_stopped(t_simulation *table);

void			destroy_simulation(t_simulation *simulation);

pthread_mutex_t			*init_forks(t_simulation *simulation);
void					destroy_forks(t_simulation *simulation);

void					*philosopher(void *data);

t_philosopher			**init_philosophers(t_simulation *simulation);
void					destroy_philosophers(t_simulation *simulation);

#endif

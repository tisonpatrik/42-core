

#include "../include/simulator.h"
/* intit_forks:
*	Allocates memory and initializes fork mutexes.
*	Returns a pointer to the fork mutex array, or NULL if an error occured.
*/
static pthread_mutex_t	*init_forks(t_table *table)
{
	pthread_mutex_t	*forks;
	unsigned int	i;

	forks = malloc(sizeof(pthread_mutex_t) * table->nb_philos);
	if (!forks)
		return (NULL);
	i = 0;
	while (i < table->nb_philos)
	{
		if (pthread_mutex_init(&forks[i], 0) != 0)
		{
			while (i-- > 0)
				pthread_mutex_destroy(&forks[i]);
			free(forks);
			return (NULL);
		}
		i++;
	}
	return (forks);
}

/* assign_forks:
*	Assigns two fork ids to each philosopher. Even-numbered philosophers
*	get their fork order switched. This is because the order in which
*	philosophers take their forks matters.
*
*	For example with 3 philos:
*		Philo #1 (id: 0) will want fork 0 and fork 1
*		Philo #2 (id: 1) will want fork 1 and fork 2
*		Philo #3 (id: 2) will want fork 2 and fork 0
*	If philo #1 takes fork 0, philo #2 takes fork 1 and philo #3 takes fork 2,
*	there is a deadlock. Each will be waiting for their second fork which is
*	in use by another philo.
*
*	Making even id philos "left-handed" helps:
*		Philo #1 (id: 0) takes fork 1 and then fork 0
*		Philo #2 (id: 1) takes fork 1 and then fork 2
*		Philo #3 (id: 2) takes fork 0 and then fork 2
*	Now, philo #1 takes fork 1, philo #3 takes fork 0 and philo #2 waits patiently.
*	Fork 2 is free for philo #3 to take, so he eats. When he is done philo #1 can
*	take fork 0 and eat. When he is done, philo #2 can finally get fork 1 and eat.
*/
static void	assign_forks(t_philosopher *philo)
{
	philo->left_fork = philo->id;
	philo->right_fork = (philo->id + 1) % philo->table->nb_philos;
	if (philo->id % 2)
	{
		philo->left_fork = (philo->id + 1) % philo->table->nb_philos;
		philo->right_fork = philo->id;
	}
}

/* init_philosophers:
*	Allocates memory for each philosopher and initializes their values.
*	Returns a pointer to the array of philosophers or NULL if
*	initialization failed.
*/
static t_philosopher	**init_philosophers(t_table *table)
{
	t_philosopher			**philosophers;
	unsigned int	i;

	philosophers = malloc(sizeof(t_philosopher) * table->nb_philos);
	if (!philosophers)
		return (NULL);
	i = 0;
	while (i < table->nb_philos)
	{
		philosophers[i] = malloc(sizeof(t_philosopher) * 1);
		if (!philosophers[i])
		{
			while (i-- > 0)
				free(philosophers[i]);
			free(philosophers);
			return (NULL);
		}
		if (pthread_mutex_init(&philosophers[i]->meal_time_lock, 0) != 0)
		{
			free(philosophers[i]);
			while (i-- > 0)
			{
				pthread_mutex_destroy(&philosophers[i]->meal_time_lock);
				free(philosophers[i]);
			}
			free(philosophers);
			return (NULL);
		}
		philosophers[i]->table = table;
		philosophers[i]->id = i;
		philosophers[i]->times_ate = 0;
		assign_forks(philosophers[i]);
		i++;
	}
	return (philosophers);
}

/* init_global_mutexes:
*	Initializes mutex locks for forks, writing and the stop simulation
*	flag.
*	Returns true if the initalizations were successful, false if
*	initilization failed.
*/
static bool	init_global_mutexes(t_table *table)
{
	table->fork_locks = init_forks(table);
	if (!table->fork_locks)
		return (false);
	if (pthread_mutex_init(&table->sim_stop_lock, 0) != 0)
		return (error_failure(STR_ERR_MUTEX, NULL, table));
	if (pthread_mutex_init(&table->write_lock, 0) != 0)
		return (error_failure(STR_ERR_MUTEX, NULL, table));
	return (true);
}

/* init_table:
*	Initializes the "dining table", the data structure containing
*	all of the program's parameters.
*	Returns a pointer to the allocated table structure, or NULL if
*	an error occured during initialization.
*/
t_table	*init_table(int ac, char **av, int i)
{
	t_table	*table;

	table = malloc(sizeof(t_table) * 1);
	if (!table)
		return (NULL);
	table->nb_philos = integer_atoi(av[i++]);
	table->time_to_die = integer_atoi(av[i++]);
	table->time_to_eat = integer_atoi(av[i++]);
	table->time_to_sleep = integer_atoi(av[i++]);
	table->must_eat_count = -1;
	if (ac - 1 == 5)
		table->must_eat_count = integer_atoi(av[i]);
	table->philosophers = init_philosophers(table);
	if (!table->philosophers)
		return (NULL);
	if (!init_global_mutexes(table))
		return (NULL);
	table->sim_stop = false;
	return (table);
}

#include "../include/simulator.h"

/* init_forks:
*	Allocates memory and initializes fork mutexes.
*	Returns a pointer to the fork mutex array, or NULL if an error occured.
*/
static pthread_mutex_t	*init_forks(t_simulation *simulation)
{
	pthread_mutex_t	*forks;
	unsigned int	i;

	forks = malloc(sizeof(pthread_mutex_t) * simulation->nb_philos);
	if (!forks)
		return (NULL);
	i = 0;
	while (i < simulation->nb_philos)
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
	philo->right_fork = (philo->id + 1) % philo->simulation->nb_philos;
	if (philo->id % 2)
	{
		philo->left_fork = (philo->id + 1) % philo->simulation->nb_philos;
		philo->right_fork = philo->id;
	}
}

/* init_philosophers:
*	Allocates memory for each philosopher and initializes their values.
*	Returns a pointer to the array of philosophers or NULL if
*	initialization failed.
*/
static t_philosopher	**init_philosophers(t_simulation *simulation)
{
	t_philosopher			**philosophers;
	unsigned int	i;

	philosophers = malloc(sizeof(t_philosopher) * simulation->nb_philos);
	if (!philosophers)
		return (NULL);
	i = 0;
	while (i < simulation->nb_philos)
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
		philosophers[i]->simulation = simulation;
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
*	Returns NULL on success, error message on failure.
*/
static char	*init_global_mutexes(t_simulation *simulation)
{
	simulation->fork_locks = init_forks(simulation);
	if (!simulation->fork_locks)
		return ("Failed to allocate fork locks");
	if (pthread_mutex_init(&simulation->sim_stop_lock, 0) != 0)
		return ("Failed to initialize sim_stop_lock");
	if (pthread_mutex_init(&simulation->write_lock, 0) != 0)
		return ("Failed to initialize write_lock");
	return (NULL);
}

/* create_simulation:
*	Initializes the simulation, the data structure containing
*	all of the program's parameters.
*	Returns t_result with simulation or error message.
*/
t_result	create_simulation(t_inputs inputs)
{
	t_simulation	*simulation;

	simulation = malloc(sizeof(t_simulation) * 1);
	if (!simulation)
		return ((t_result){NULL, "Memory allocation failed"});
	simulation->nb_philos = inputs.nb_philos;
	simulation->time_to_die = inputs.time_to_die;
	simulation->time_to_eat = inputs.time_to_eat;
	simulation->time_to_sleep = inputs.time_to_sleep;
	simulation->must_eat_count = inputs.must_eat_count;
	simulation->philosophers = init_philosophers(simulation);
	if (!simulation->philosophers)
		return ((t_result){NULL, "Failed to initialize philosophers"});
	char *err = init_global_mutexes(simulation);
	if (err)
		return ((t_result){NULL, err});
	simulation->sim_stop = false;
	return ((t_result){simulation, NULL});
}

/* destroy_mutexes:
*	Destroys every mutex created by the program: fork locks, meal locks,
*	the write and simulation stopper lock.
*/
static void	destroy_mutexes(t_simulation *simulation)
{
	unsigned int	i;

	i = 0;
	while (i < simulation->nb_philos)
	{
		pthread_mutex_destroy(&simulation->fork_locks[i]);
		pthread_mutex_destroy(&simulation->philosophers[i]->meal_time_lock);
		i++;
	}
	pthread_mutex_destroy(&simulation->write_lock);
	pthread_mutex_destroy(&simulation->sim_stop_lock);
}

/* free_simulation:
*	Frees all of the memory allocated by the program.
*/
static void	free_simulation(t_simulation *simulation)
{
	unsigned int	i;

	if (!simulation)
		return;
	if (simulation->fork_locks != NULL)
	{
		free(simulation->fork_locks);
		simulation->fork_locks = NULL;
	}
	if (simulation->philosophers != NULL)
	{
		i = 0;
		while (i < simulation->nb_philos)
		{
			if (simulation->philosophers[i] != NULL)
				free(simulation->philosophers[i]);
			i++;
		}
		free(simulation->philosophers);
		simulation->philosophers = NULL;
	}
	free(simulation);
}

/* destroy_simulation:
*	Destroys the simulation: destroys mutexes and frees memory.
*/
void	destroy_simulation(t_simulation *simulation)
{
	if (!simulation)
		return;
	destroy_mutexes(simulation);
	free_simulation(simulation);
}
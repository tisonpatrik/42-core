#include "../include/simulation.h"

/* init_global_mutexes:
*	Initializes mutex locks for writing and the stop simulation flag.
*	Returns NULL on success, error message on failure.
*/
static char	*init_global_mutexes(t_simulation *simulation)
{
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
		return ((t_result){NULL, false});
	simulation->nb_philos = inputs.nb_philos;
	simulation->time_to_die = inputs.time_to_die;
	simulation->time_to_eat = inputs.time_to_eat;
	simulation->time_to_sleep = inputs.time_to_sleep;
	simulation->must_eat_count = inputs.must_eat_count;
	simulation->philosophers = init_philosophers(simulation);
	if (!simulation->philosophers)
		return ((t_result){NULL, false});
	simulation->fork_locks = init_forks(simulation);
	if (!simulation->fork_locks)
		return ((t_result){NULL, false});
	char *err = init_global_mutexes(simulation);
	if (err)
		return ((t_result){NULL, false});
	simulation->sim_stop = false;
	return ((t_result){simulation, true});
}

/* destroy_mutexes:
*	Destroys global mutexes: write and simulation stopper lock.
*/
static void	destroy_mutexes(t_simulation *simulation)
{
	pthread_mutex_destroy(&simulation->write_lock);
	pthread_mutex_destroy(&simulation->sim_stop_lock);
}

/* free_simulation:
*	Frees the simulation struct.
*/
static void	free_simulation(t_simulation *simulation)
{
	if (!simulation)
		return;
	free(simulation);
}

/* destroy_simulation:
*	Destroys the simulation: destroys all mutexes and frees all memory.
*/
void	destroy_simulation(t_simulation *simulation)
{
	if (!simulation)
		return;
	destroy_forks(simulation);
	destroy_philosophers(simulation);
	destroy_mutexes(simulation);
	free_simulation(simulation);
}

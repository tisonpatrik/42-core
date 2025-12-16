#include "../include/simulation.h"

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

/*
* Helper function to free the array of philosophers up to 'count'.
* It handles both partial cleanup (on init failure) and full destruction.
*/
static void free_philosophers_array(t_philosopher **philos, unsigned int count)
{
    unsigned int i;

    i = 0;
    while (i < count)
    {
        if (philos[i])
        {
            pthread_mutex_destroy(&philos[i]->meal_time_lock);
            free(philos[i]);
        }
        i++;
    }
    free(philos);
}

/* init_single_philosopher:
*	Allocates and initializes a single philosopher.
*	Returns the philosopher or NULL on failure.
*/
static t_philosopher	*init_single_philosopher(t_simulation *simulation, unsigned int id)
{
	t_philosopher	*philo;

	philo = malloc(sizeof(t_philosopher));
	if (!philo)
		return (NULL);
	if (pthread_mutex_init(&philo->meal_time_lock, 0) != 0)
	{
		free(philo);
		return (NULL);
	}
	philo->simulation = simulation;
	philo->id = id;
	philo->times_ate = 0;
	assign_forks(philo);
	return (philo);
}

/*
* init_philosophers:
* Allocates memory for each philosopher and initializes their values.
* Uses the helper function for cleanup if something goes wrong.
*/
t_philosopher **init_philosophers(t_simulation *simulation)
{
    t_philosopher **philosophers;
    unsigned int i;

    philosophers = malloc(sizeof(t_philosopher *) * simulation->nb_philos);
    if (!philosophers)
        return (NULL);
    i = 0;
    while (i < simulation->nb_philos)
    {
        philosophers[i] = init_single_philosopher(simulation, i);
        if (!philosophers[i])
        {
            // Reuse the helper to clean up valid philos created so far
            free_philosophers_array(philosophers, i);
            return (NULL);
        }
        i++;
    }
    return (philosophers);
}

/*
* destroy_philosophers:
* Destroys philosopher mutexes and frees memory using the same helper.
*/
void destroy_philosophers(t_simulation *simulation)
{
    if (!simulation->philosophers)
        return;
    free_philosophers_array(simulation->philosophers, simulation->nb_philos);
    simulation->philosophers = NULL;
}

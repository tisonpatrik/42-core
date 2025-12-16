#include "../include/simulator.h"

/* init_forks:
*	Allocates memory and initializes fork mutexes.
*	Returns a pointer to the fork mutex array, or NULL if an error occured.
*/
pthread_mutex_t	*init_forks(t_simulation *simulation)
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

/* destroy_forks:
*	Destroys fork mutexes.
*/
void	destroy_forks(t_simulation *simulation)
{
	unsigned int	i;

	i = 0;
	while (i < simulation->nb_philos)
	{
		pthread_mutex_destroy(&simulation->fork_locks[i]);
		i++;
	}
}
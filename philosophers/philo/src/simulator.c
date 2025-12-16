#include "../include/simulation.h"

char	*start_simulation(t_simulation *simulation)
{
	unsigned int	i;

	simulation->start_time = get_time_in_ms() + (simulation->nb_philos * 2 * 10);
	i = 0;
	while (i < simulation->nb_philos)
	{
		if (pthread_create(&simulation->philosophers[i]->thread, NULL,
				&philosopher, simulation->philosophers[i]) != 0)
			return ("Thread creation failed");
		i++;
	}
	if (simulation->nb_philos > 1)
	{
		if (pthread_create(&simulation->grim_reaper, NULL,
				&grim_reaper, simulation) != 0)
			return ("Thread creation failed");
	}
	return (NULL);
}

void	stop_simulation(t_simulation	*simulation)
{
	unsigned int	i;

	i = 0;
	while (i < simulation->nb_philos)
	{
		pthread_join(simulation->philosophers[i]->thread, NULL);
		i++;
	}
	if (simulation->nb_philos > 1)
		pthread_join(simulation->grim_reaper, NULL);
	if (simulation->must_eat_count != -1)
	{
		unsigned int i, full_count = 0;
		for (i = 0; i < simulation->nb_philos; i++)
		{
			if (simulation->philosophers[i]->times_ate >= (unsigned int)simulation->must_eat_count)
				full_count++;
		}
		printf("%d/%d philosophers had at least %d meals.\n",
			full_count, simulation->nb_philos, simulation->must_eat_count);
	}
}


#include "../include/simulator.h"
#include <stdlib.h>

static void setup_arena_memory(t_simulation* simulation, int count_of_philosophers)
{
    int i;

    simulation->philosophers = malloc(sizeof(t_philosopher) * count_of_philosophers);
    if (!simulation->philosophers)
        return;
    simulation->forks = malloc(sizeof(t_fork) * count_of_philosophers);
    if (!simulation->forks)
    {
        free(simulation->philosophers);
        return;
    }
    i = 0;
    while (i < count_of_philosophers)
    {
        simulation->philosophers[i].id = i + 1;
        simulation->philosophers[i].is_eating = false;
        simulation->philosophers[i].is_sleeping = false;
        simulation->philosophers[i].is_thinking = false;
        simulation->forks[i].id = i + 1;
        simulation->forks[i].is_used = false;
        i++;
    }
}

t_simulation *create_simulation(t_inputs inputs) {
  t_simulation *simulation;

  simulation = malloc(sizeof(*simulation));
  if(!simulation)
      return NULL;
  setup_arena_memory(simulation, inputs.count_of_philosophers);
  if (!simulation->philosophers || !simulation->forks)
  {
      if (simulation->philosophers)
          free(simulation->philosophers);
      if (simulation->forks)
          free(simulation->forks);
      free(simulation);
      return NULL;
  }
  simulation->count_of_philosophers = inputs.count_of_philosophers;
  simulation->count_of_forks = inputs.count_of_philosophers;
  simulation->time_to_die = inputs.time_to_die;
  simulation->time_to_eat = inputs.time_to_eat;
  simulation->time_to_sleep = inputs.time_to_sleep;
  simulation->number_of_times_each_philosopher_must_eat = inputs.number_of_times_each_philosopher_must_eat;
  return simulation;
}

void destroy_simulation(t_simulation* simulation)
{
	if (!simulation)
		return;
	if (simulation->philosophers)
		free(simulation->philosophers);
	if (simulation->forks)
		free(simulation->forks);
	free(simulation);
}

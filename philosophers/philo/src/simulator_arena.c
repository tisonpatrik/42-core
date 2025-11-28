
#include "../include/simulator.h"
#include <stdlib.h>

static size_t get_arena_size(int count_of_philosophers)
{
    size_t size;
    size = sizeof(t_philosopher) * count_of_philosophers;
    size += sizeof(t_fork) * count_of_philosophers;
    return size;
}

static void setup_arena_memory(t_simulation* simulation, int count_of_philosophers)
{
    int i;

    simulation->philosophers = ft_arena_alloc(simulation->arena, sizeof(t_philosopher) * count_of_philosophers);
    if (!simulation->philosophers)
        return;
    simulation->forks = ft_arena_alloc(simulation->arena, sizeof(t_fork) * count_of_philosophers);
    if (!simulation->forks)
        return;
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
  size_t arena_size;

  arena_size = get_arena_size(inputs.count_of_philosophers);
  simulation = malloc(sizeof(*simulation));
  if(!simulation)
      return NULL;
  simulation -> arena = ft_arena_create(arena_size);
  if(!simulation->arena)
  {
      free(simulation);
      return NULL;
  }
  setup_arena_memory(simulation, inputs.count_of_philosophers);
  simulation->count_of_philosophers = inputs.count_of_philosophers;
  simulation->count_of_forks = inputs.count_of_philosophers;
  return simulation;
}

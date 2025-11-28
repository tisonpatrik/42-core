#include "../include/simulator.h"


static int init_forks(t_fork* forks, int count)
{
    int i;

    i = 0;
    while (i < count)
    {
        forks[i].id = i + 1;
        if (pthread_mutex_init(&forks[i].mutex, NULL) != 0)
        {
            while (i > 0)
            {
                i--;
                pthread_mutex_destroy(&forks[i].mutex);
            }
            return (0);
        }
        i++;
    }
    return (1);
}

static void init_philosopher(t_philosopher* philo, int id, int count, t_inputs inputs, long long start_time)
{
    philo->id = id;
    philo->times_eaten = 0;
    philo->last_meal_time = start_time;
    philo->state_start_time = start_time;
    philo->state = IS_THINKING;
    philo->left_fork_id = id - 1;
    philo->right_fork_id = id % count;
    philo->start_time = start_time;
}

static int setup_arena_memory(t_simulation* simulation, t_inputs inputs, long long start_time)
{
    int i;

    simulation->philosophers = malloc(sizeof(t_philosopher) * inputs.count_of_philosophers);
    if (!simulation->philosophers)
        return (0);
    simulation->forks = malloc(sizeof(t_fork) * inputs.count_of_philosophers);
    if (!simulation->forks)
    {
        free(simulation->philosophers);
        return (0);
    }
    if (!init_forks(simulation->forks, inputs.count_of_philosophers))
    {
        free(simulation->philosophers);
        free(simulation->forks);
        return (0);
    }
    i = 0;
    while (i < inputs.count_of_philosophers)
    {
        init_philosopher(&simulation->philosophers[i], i + 1, inputs.count_of_philosophers, inputs, start_time);
        i++;
    }
    return (1);
}

static long long get_current_time_ms(void)
{
	struct timeval tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000LL + tv.tv_usec / 1000);
}

t_simulation *create_simulation(t_inputs inputs) {
  t_simulation *simulation;
  long long start_time;

  simulation = malloc(sizeof(*simulation));
  if(!simulation)
      return NULL;
  start_time = get_current_time_ms();
  if (!setup_arena_memory(simulation, inputs, start_time))
  {
      free(simulation);
      return NULL;
  }
  if (pthread_mutex_init(&simulation->print_mutex, NULL) != 0)
  {
      destroy_simulation(simulation);
      return NULL;
  }
  if (pthread_mutex_init(&simulation->death_mutex, NULL) != 0)
  {
      pthread_mutex_destroy(&simulation->print_mutex);
      destroy_simulation(simulation);
      return NULL;
  }
  simulation->count_of_philosophers = inputs.count_of_philosophers;
  simulation->count_of_forks = inputs.count_of_philosophers;
  simulation->time_to_die = inputs.time_to_die;
  simulation->time_to_eat = inputs.time_to_eat;
  simulation->time_to_sleep = inputs.time_to_sleep;
  simulation->number_of_times_each_philosopher_must_eat = inputs.number_of_times_each_philosopher_must_eat;
  simulation->start_time = start_time;
  simulation->simulation_running = true;
  return simulation;
}

void destroy_simulation(t_simulation* simulation)
{
	int i;

	if (!simulation)
		return;
	if (simulation->philosophers)
		free(simulation->philosophers);
	if (simulation->forks)
	{
		i = 0;
		while (i < simulation->count_of_forks)
		{
			pthread_mutex_destroy(&simulation->forks[i].mutex);
			i++;
		}
		free(simulation->forks);
	}
	pthread_mutex_destroy(&simulation->print_mutex);
	pthread_mutex_destroy(&simulation->death_mutex);
	free(simulation);
}

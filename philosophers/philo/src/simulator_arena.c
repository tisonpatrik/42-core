#include "../include/simulator.h"


static int init_forks(t_fork* forks, int count)
{
	int i;

	i = 0;
	while (i < count)
	{
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

static void init_philosopher(t_philosopher* philo, int id, int count, long long start_time, t_context* context)
{
	philo->id = id;
	philo->times_eaten = 0;
	philo->last_meal_time = start_time;
	philo->state_start_time = start_time;
	philo->left_fork_id = id - 1;
	philo->right_fork_id = id % count;
	philo->start_time = start_time;
	philo->context = context;
}

static int setup_arena_memory(t_context* context, t_inputs inputs)
{
	context->forks = malloc(sizeof(t_fork) * inputs.count_of_philosophers);
	if (!context->forks)
		return (0);
	if (!init_forks(context->forks, inputs.count_of_philosophers))
	{
		free(context->forks);
		return (0);
	}
	return (1);
}

static long long get_current_time_ms(void)
{
	struct timeval tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000LL + tv.tv_usec / 1000);
}

static int create_philosopher_threads(t_philosopher* philosophers, int count)
{
	int i;

	i = 0;
	while (i < count)
	{
		if (pthread_create(&philosophers[i].thread, NULL, do_philosophy, &philosophers[i]) != 0)
		{
			while (i > 0)
			{
				i--;
				pthread_join(philosophers[i].thread, NULL);
			}
			return (0);
		}
		i++;
	}
	return (1);
}

t_context *create_context(t_inputs inputs)
{
	t_context *context;
	long long start_time;

	context = malloc(sizeof(*context));
	if (!context)
		return NULL;
	start_time = get_current_time_ms();
	context->count_of_philosophers = inputs.count_of_philosophers;
	context->count_of_forks = inputs.count_of_philosophers;
	context->time_to_die = inputs.time_to_die;
	context->time_to_eat = inputs.time_to_eat;
	context->time_to_sleep = inputs.time_to_sleep;
	context->number_of_times_each_philosopher_must_eat = inputs.number_of_times_each_philosopher_must_eat;
	context->start_time = start_time;
	context->simulation_running = true;
	context->is_dead = false;
	if (!setup_arena_memory(context, inputs))
	{
		free(context);
		return NULL;
	}
	if (pthread_mutex_init(&context->print_mutex, NULL) != 0)
	{
		destroy_context(context);
		return NULL;
	}
	if (pthread_mutex_init(&context->death_mutex, NULL) != 0)
	{
		pthread_mutex_destroy(&context->print_mutex);
		destroy_context(context);
		return NULL;
	}
	return context;
}

t_philosopher* create_philosophers(t_context* context, t_inputs inputs)
{
	t_philosopher* philosophers;
	int i;

	philosophers = malloc(sizeof(t_philosopher) * inputs.count_of_philosophers);
	if (!philosophers)
		return NULL;
	i = 0;
	while (i < inputs.count_of_philosophers)
	{
		init_philosopher(&philosophers[i], i + 1, inputs.count_of_philosophers, context->start_time, context);
		i++;
	}
	if (!create_philosopher_threads(philosophers, inputs.count_of_philosophers))
	{
		free(philosophers);
		return NULL;
	}
	return philosophers;
}

void destroy_context(t_context* context)
{
	int i;

	if (!context)
		return;
	if (context->forks)
	{
		i = 0;
		while (i < context->count_of_forks)
		{
			pthread_mutex_destroy(&context->forks[i].mutex);
			i++;
		}
		free(context->forks);
	}
	pthread_mutex_destroy(&context->print_mutex);
	pthread_mutex_destroy(&context->death_mutex);
	free(context);
}

void destroy_philosophers(t_philosopher* philosophers, int count)
{
	if (!philosophers)
		return;
	free(philosophers);
}

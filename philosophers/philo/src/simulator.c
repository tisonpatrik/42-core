

#include "../include/simulator.h"
#include <bits/pthreadtypes.h>
#include <pthread.h>
#include <unistd.h>


void do_sleeping(int time)
{
    int success = usleep(time);
    if (success!= 0)
    {
        exit(0);
    }
}

void do_thinking(int time)
{
    int success = usleep(time);
    if (success!= 0)
    {
        exit(0);
    }
}

void do_eating(int time_for_eating, pthread_mutex_t leva_vidlicka, pthread_mutex_t prava_vidlicka)
{
    int success = pthread_mutex_lock(&leva_vidlicka);
    if (success!= 0)
    {
        exit(0);
    }

    success = pthread_mutex_lock(&prava_vidlicka);
    if (success!= 0)
    {
        exit(0);
    }

    success = usleep(time_for_eating);
    if (success!= 0)
    {
        exit(0);
    }
    success =pthread_mutex_unlock(&leva_vidlicka);

    if (success!= 0)
    {
        exit(0);
    }
    success = pthread_mutex_unlock(&prava_vidlicka);

    if (success!= 0)
    {
        exit(0);
    }
}

void *do_philosophy(void *arg)
{
    t_philosopher *philo = (t_philosopher *)arg;
    return (NULL);
}

void run_simulation(t_context* context, t_philosopher* philosophers)
{
	int i;

	i = 0;
	while (i < context->count_of_philosophers)
	{
		pthread_join(philosophers[i].thread, NULL);
		i++;
	}
}


#include "../include/simulator.h"
#include <stdio.h>

void run_simulation(t_simulation* simulation)
{
    printf("simulation created\n");
    printf("count_of_philosophers: %d\n", simulation->count_of_philosophers);
    printf("count_of_forks: %d\n", simulation->count_of_forks);
    printf("time_to_die: %d\n", simulation->time_to_die);
    printf("time_to_eat: %d\n", simulation->time_to_eat);
    printf("time_to_sleep: %d\n", simulation->time_to_sleep);
    printf("number_of_times_each_philosopher_must_eat: %d\n", simulation->number_of_times_each_philosopher_must_eat);
    printf("simulating...\n");
}

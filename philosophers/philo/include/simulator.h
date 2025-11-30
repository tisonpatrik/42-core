

#ifndef SIMULATOR_H
#define SIMULATOR_H

#include <pthread.h>
#include <stdbool.h>
#include "../include/validator.h"
#include <stdlib.h>
#include <sys/time.h>

typedef struct s_fork{
    int id;
    pthread_mutex_t mutex;
} t_fork;

typedef struct s_context t_context;

typedef struct s_philosopher{
    int id;
    pthread_t thread;
    int times_eaten;
    long long last_meal_time;
    long long state_start_time;
    int left_fork_id;
    int right_fork_id;
    long long start_time;
    t_context* context;
} t_philosopher;

typedef struct s_context{
    int count_of_philosophers;
    int count_of_forks;
    int time_to_die;
    int time_to_eat;
    int time_to_sleep;
    int number_of_times_each_philosopher_must_eat;
    long long start_time;
    bool simulation_running;
    t_fork* forks;
    pthread_mutex_t print_mutex;
    pthread_mutex_t death_mutex;
    bool is_dead;
} t_context;


t_context* create_context(t_inputs inputs);
t_philosopher* create_philosophers(t_context* context, t_inputs inputs);
void destroy_context(t_context* context);
void destroy_philosophers(t_philosopher* philosophers, int count);
void run_simulation(t_context* context, t_philosopher* philosophers);

void *do_philosophy(void *arg);


#endif

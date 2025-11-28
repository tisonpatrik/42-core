

#ifndef SIMULATOR_H
#define SIMULATOR_H

#include <pthread.h>
#include <stdbool.h>
#include "../include/validator.h"
#include <stdlib.h>
#include <sys/time.h>

typedef enum e_philosopher_state{
    IS_THINKING,
    IS_SLEEPING,
    IS_EATING
}   t_philosopher_state;



typedef struct s_fork{
    int id;
    pthread_mutex_t mutex;
} t_fork;

typedef struct s_philosopher{
    int id;
    pthread_t thread;
    int times_eaten;
    long long last_meal_time;
    long long state_start_time;
    t_philosopher_state state;
    int left_fork_id;
    int right_fork_id;
    int time_to_die;
    int time_to_eat;
    int time_to_sleep;
    int number_of_times_each_philosopher_must_eat;
    long long start_time;
} t_philosopher;

typedef struct s_simulation{
    int count_of_philosophers;
    int count_of_forks;
    int time_to_die;
    int time_to_eat;
    int time_to_sleep;
    int number_of_times_each_philosopher_must_eat;
    long long start_time;
    bool simulation_running;
    t_philosopher* philosophers;
    t_fork* forks;
    pthread_mutex_t print_mutex;
    pthread_mutex_t death_mutex;
} t_simulation;


t_simulation* create_simulation(t_inputs inputs);
void run_simulation(t_simulation* simulation);
void destroy_simulation(t_simulation* simulation);


#endif

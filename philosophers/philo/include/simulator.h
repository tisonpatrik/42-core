

#ifndef SIMULATOR_H
#define SIMULATOR_H

#include <stdbool.h>
#include "../include/validator.h"
#include "../libft/include/libft.h"

typedef struct s_philosopher{
    int id; bool is_eating;
    bool is_sleeping;
    bool is_thinking; } t_philosopher;


typedef struct s_fork{
    int id;
    bool is_used; } t_fork;

typedef struct s_simulation{
    t_arena *arena;
    int count_of_philosophers;
    int count_of_forks;
    t_philosopher* philosophers;
    t_fork* forks;
}        t_simulation;


t_simulation* create_simulation(t_inputs inputs);
void run_simulation(t_simulation* simulation);


#endif



#ifndef SIMULATOR_H
#define SIMULATOR_H

#include <stdbool.h>

typedef struct s_philosopher{
    int id; bool is_eating;
    bool is_sleeping;
    bool is_thinking; } t_philosopher;


typedef struct s_fork{
    int id;
    bool is_used; } t_fork;

typedef struct s_simulation{
    int count_of_philosophers; t_philosopher* philosophers;
    t_fork* forks; } t_simulation;


void run();
#endif

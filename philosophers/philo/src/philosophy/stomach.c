#include "../../include/simulation.h"
#include "../../include/philosophy.h"

static void update_meal_stats(t_philosopher *philo)
{
    pthread_mutex_lock(&philo->meal_time_lock);
    philo->last_meal = get_time_in_ms();
    pthread_mutex_unlock(&philo->meal_time_lock);
}

static void increment_meal_counter(t_philosopher *philo)
{
    if (has_simulation_stopped(philo->table))
        return ;
    pthread_mutex_lock(&philo->meal_time_lock);
    philo->times_ate += 1;
    pthread_mutex_unlock(&philo->meal_time_lock);
}

// Orchestrátor jídla - spojuje zdroje a metabolismus
void do_eating(t_philosopher *philo)
{
    take_forks(philo);

    write_status(philo, "is eating");
    update_meal_stats(philo);
    precise_sleep(philo->table, philo->table->time_to_eat);
    increment_meal_counter(philo);
    drop_forks(philo);
}

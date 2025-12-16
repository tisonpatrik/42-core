#include "../../include/philosophy.h"

void take_forks(t_philosopher *philo)
{
    if (philo->id % 2 == 0)
    {
        pthread_mutex_lock(&philo->table->fork_locks[philo->fork_right]);
        write_status(philo, "has taken a fork");
        pthread_mutex_lock(&philo->table->fork_locks[philo->fork_left]);
        write_status(philo, "has taken a fork");
    }
    else
    {
        pthread_mutex_lock(&philo->table->fork_locks[philo->fork_left]);
        write_status(philo, "has taken a fork");
        pthread_mutex_lock(&philo->table->fork_locks[philo->fork_right]);
        write_status(philo, "has taken a fork");
    }
}

void drop_forks(t_philosopher *philo)
{
    pthread_mutex_unlock(&philo->table->fork_locks[philo->fork_right]);
    pthread_mutex_unlock(&philo->table->fork_locks[philo->fork_left]);
}

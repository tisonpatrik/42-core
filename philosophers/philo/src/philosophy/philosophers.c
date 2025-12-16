#include "../../include/simulation.h"

static void write_status(t_philosopher *philo, char *status)
{
    pthread_mutex_lock(&philo->table->write_lock);
    if (!has_simulation_stopped(philo->table))
    {
        printf("%ld %d %s\n",
            get_time_in_ms() - philo->table->start_time,
            philo->id + 1,
            status);
    }
    pthread_mutex_unlock(&philo->table->write_lock);
}

static void philo_sleep(t_table *table, time_t sleep_time)
{
    time_t wake_up;

    wake_up = get_time_in_ms() + sleep_time;
    while (get_time_in_ms() < wake_up)
    {
        if (has_simulation_stopped(table))
            break;
        usleep(100);
    }
}

static void perform_eat_and_sleep(t_philosopher *philo)
{
    // 1. Take Forks
    pthread_mutex_lock(&philo->table->fork_locks[philo->fork_left]);
    write_status(philo, "has taken a fork");

    pthread_mutex_lock(&philo->table->fork_locks[philo->fork_right]);
    write_status(philo, "has taken a fork");

    // 2. Eat
    write_status(philo, "is eating");
    pthread_mutex_lock(&philo->meal_time_lock);
    philo->last_meal = get_time_in_ms();
    pthread_mutex_unlock(&philo->meal_time_lock);

    philo_sleep(philo->table, philo->table->time_to_eat);

    if (!has_simulation_stopped(philo->table))
    {
        pthread_mutex_lock(&philo->meal_time_lock);
        philo->times_ate += 1;
        pthread_mutex_unlock(&philo->meal_time_lock);
    }

    // 3. Release Forks
    pthread_mutex_unlock(&philo->table->fork_locks[philo->fork_right]);
    pthread_mutex_unlock(&philo->table->fork_locks[philo->fork_left]);

    // 4. Sleep
    write_status(philo, "is sleeping");
    philo_sleep(philo->table, philo->table->time_to_sleep);
}

static void perform_thinking(t_philosopher *philo, bool silent)
{
    time_t time_to_think;

    pthread_mutex_lock(&philo->meal_time_lock);
    time_to_think = (philo->table->time_to_die
            - (get_time_in_ms() - philo->last_meal)
            - philo->table->time_to_eat) / 2;
    pthread_mutex_unlock(&philo->meal_time_lock);

    if (time_to_think < 0)
        time_to_think = 0;
    if (time_to_think == 0 && silent == true)
        time_to_think = 1;
    if (time_to_think > 600)
        time_to_think = 200;

    if (!silent)
        write_status(philo, "is thinking");

    philo_sleep(philo->table, time_to_think);
}

static void *handle_single_philosopher(t_philosopher *philo)
{
    pthread_mutex_lock(&philo->table->fork_locks[philo->fork_left]);
    write_status(philo, "has taken a fork");

    philo_sleep(philo->table, philo->table->time_to_die);

    // Note: We don't print "died" here, Reaper does it.
    pthread_mutex_unlock(&philo->table->fork_locks[philo->fork_left]);
    return (NULL);
}

void *do_philosophy(void *data)
{
    t_philosopher *philo;

    philo = (t_philosopher *)data;
    if (philo->table->must_eat_count == 0)
        return (NULL);

    pthread_mutex_lock(&philo->meal_time_lock);
    philo->last_meal = philo->table->start_time;
    pthread_mutex_unlock(&philo->meal_time_lock);

    sim_start_delay(philo->table->start_time);

    if (philo->table->time_to_die == 0)
        return (NULL);

    if (philo->table->nb_philos == 1)
        return (handle_single_philosopher(philo));
    else if (philo->id % 2)
        perform_thinking(philo, true); // Silent think for strict synchronization

    while (!has_simulation_stopped(philo->table))
    {
        perform_eat_and_sleep(philo);
        perform_thinking(philo, false);
    }
    return (NULL);
}

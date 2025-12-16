#include "../include/simulation.h"

/* philo_sleep:
*	Pauses the philosopher thread for a certain amount of time in miliseconds.
*	Periodically checks to see if the simulation has ended during the sleep
*	time and cuts the sleep short if it has.
*/
static void	philo_sleep(t_simulation *simulation, time_t sleep_time)
{
	time_t	wake_up;

	wake_up = get_time_in_ms() + sleep_time;
	while (get_time_in_ms() < wake_up)
	{
		if (has_simulation_stopped(simulation))
			break ;
		usleep(100);
	}
}

/* perform_eat_and_sleep:
*	When a philosopher is ready to eat, he will wait for his fork mutexes to
*	be unlocked before locking them. Then the philosopher will eat for a certain
*	amount of time. The time of the last meal is recorded at the beginning of
*	the meal, not at the end, as per the subject's requirements.
*/
static bool	perform_eat_and_sleep(t_philosopher *philo)
{
	pthread_mutex_lock(&philo->simulation->fork_locks[philo->left_fork]);
	if (!has_simulation_stopped(philo->simulation))
		printf("%ld %d has taken a fork\n",
			get_time_in_ms() - philo->simulation->start_time, philo->id + 1);
	pthread_mutex_lock(&philo->simulation->fork_locks[philo->right_fork]);
	if (!has_simulation_stopped(philo->simulation))
		printf("%ld %d has taken a fork\n",
			get_time_in_ms() - philo->simulation->start_time, philo->id + 1);
	if (!has_simulation_stopped(philo->simulation))
		printf("%ld %d is eating\n",
			get_time_in_ms() - philo->simulation->start_time, philo->id + 1);
	pthread_mutex_lock(&philo->meal_time_lock);
	philo->last_meal = get_time_in_ms();
	pthread_mutex_unlock(&philo->meal_time_lock);
	philo_sleep(philo->simulation, philo->simulation->time_to_eat);
	if (has_simulation_stopped(philo->simulation) == false)
	{
		pthread_mutex_lock(&philo->meal_time_lock);
		philo->times_ate += 1;
		pthread_mutex_unlock(&philo->meal_time_lock);
	}
	if (!has_simulation_stopped(philo->simulation))
		printf("%ld %d is sleeping\n",
			get_time_in_ms() - philo->simulation->start_time, philo->id + 1);
	pthread_mutex_unlock(&philo->simulation->fork_locks[philo->right_fork]);
	pthread_mutex_unlock(&philo->simulation->fork_locks[philo->left_fork]);
	philo_sleep(philo->simulation, philo->simulation->time_to_sleep);
	return (true);
}

/* perform_thinking:
*	Once a philosopher is done sleeping, he will think for a certain
*	amount of time before starting to eat again.
*	The time_to_think is calculated depending on how long it has been
*	since the philosopher's last meal, the time_to_eat and the time_to_die
*	to determine when the philosopher will be hungry again.
*	This helps stagger philosopher's eating routines to avoid forks being
*	needlessly monopolized by one philosopher to the detriment of others.
*/
static bool	perform_thinking(t_philosopher *philo, bool silent)
{
	time_t	time_to_think;

	pthread_mutex_lock(&philo->meal_time_lock);
	time_to_think = (philo->simulation->time_to_die
			- (get_time_in_ms() - philo->last_meal)
			- philo->simulation->time_to_eat) / 2;
	pthread_mutex_unlock(&philo->meal_time_lock);
	if (time_to_think < 0)
		time_to_think = 0;
	if (time_to_think == 0 && silent == true)
		time_to_think = 1;
	if (time_to_think > 600)
		time_to_think = 200;
	if (silent == false && !has_simulation_stopped(philo->simulation))
		printf("%ld %d is thinking\n",
			get_time_in_ms() - philo->simulation->start_time, philo->id + 1);
	philo_sleep(philo->simulation, time_to_think);
	return (true);
}

/* handle_single_philosopher:
*	This routine is invoked when there is only a single philosopher.
*	A single philosopher only has one fork, and so cannot eat. The
*	philosopher will pick up that fork, wait as long as time_to_die and die.
*	This is a separate routine to make sure that the thread does not get
*	stuck waiting for the second fork in the eat routine.
*/
static void	*handle_single_philosopher(t_philosopher *philo)
{
	pthread_mutex_lock(&philo->simulation->fork_locks[philo->left_fork]);
	if (!has_simulation_stopped(philo->simulation))
		printf("%ld %d has taken a fork\n",
			get_time_in_ms() - philo->simulation->start_time, philo->id + 1);
	philo_sleep(philo->simulation, philo->simulation->time_to_die);
	if (!has_simulation_stopped(philo->simulation))
		printf("%ld %d died\n",
			get_time_in_ms() - philo->simulation->start_time, philo->id + 1);
	pthread_mutex_unlock(&philo->simulation->fork_locks[philo->left_fork]);
	return (NULL);
}

/* philosopher:
*	The philosopher thread routine. The philosopher must eat, sleep
*	and think. In order to avoid conflicts between philosopher threads,
*	philosophers with an even id start by thinking, which delays their
*	meal time by a small margin. This allows odd-id philosophers to
*	grab their forks first, avoiding deadlocks.
*/

void    *philosopher(void *data)
{
	t_philosopher	*philo;

	philo = (t_philosopher *)data;
	if (philo->simulation->must_eat_count == 0)
		return (NULL);
	pthread_mutex_lock(&philo->meal_time_lock);
	philo->last_meal = philo->simulation->start_time;
	pthread_mutex_unlock(&philo->meal_time_lock);
	sim_start_delay(philo->simulation->start_time);
	if (philo->simulation->time_to_die == 0)
		return (NULL);
	if (philo->simulation->nb_philos == 1)
		return (handle_single_philosopher(philo));
	else if (philo->id % 2)
		perform_thinking(philo, true);
	while (has_simulation_stopped(philo->simulation) == false)
	{
		perform_eat_and_sleep(philo);
		perform_thinking(philo, false);
	}
	return (NULL);
}

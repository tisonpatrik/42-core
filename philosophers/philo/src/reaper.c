#include "../include/simulator.h"

/* set_sim_stop_flag:
*	Sets the simulation stop flag to true or false. Only the grim
*	reaper thread can set this flag. If the simulation stop flag is
*	set to true, that means the simulation has met an end condition.
*/
static void	set_sim_stop_flag(t_simulation *simulation, bool state)
{
	pthread_mutex_lock(&simulation->sim_stop_lock);
		simulation->sim_stop = state;
	pthread_mutex_unlock(&simulation->sim_stop_lock);
}

/* has_simulation_stopped:
*	Checks whether the simulation is at an end. The stop flag
*	is protected by a mutex lock to allow any thread to check
*	the simulation status without conflict.
*	Returns true if the simulation stop flag is set to true,
*	false if the flag is set to false.
*/
bool	has_simulation_stopped(t_simulation *simulation)
{
	bool	r;

	r = false;
	pthread_mutex_lock(&simulation->sim_stop_lock);
	if (simulation->sim_stop == true)
		r = true;
	pthread_mutex_unlock(&simulation->sim_stop_lock);
	return (r);
}

/* kill_philo:
*	Checks if the philosopher must be killed by comparing the
*	time since the philosopher's last meal and the time_to_die parameter.
*	If it is time for the philosopher to die, sets the simulation stop
*	flag and displays the death status.
*	Returns true if the philosopher has been killed, false if not.
*/
static bool	kill_philo(t_philosopher *philo)
{
	time_t	time;

	time = get_time_in_ms();
	if ((time - philo->last_meal) >= philo->simulation->time_to_die)
	{
		set_sim_stop_flag(philo->simulation, true);
		printf("%ld %d died\n",
			get_time_in_ms() - philo->simulation->start_time, philo->id + 1);
		pthread_mutex_unlock(&philo->meal_time_lock);
		return (true);
	}
	return (false);
}

/* end_condition_reached:
*	Checks each philosopher to see if one of two end conditions
*	has been reached. Stops the simulation if a philosopher needs
*	to be killed, or if every philosopher has eaten enough.
*	Returns true if an end condition has been reached, false if not.
*/
static bool	end_condition_reached(t_simulation *simulation)
{
	unsigned int	i;
	bool			all_ate_enough;

	all_ate_enough = true;
	i = 0;
	while (i < simulation->nb_philos)
	{
		pthread_mutex_lock(&simulation->philosophers[i]->meal_time_lock);
		if (kill_philo(simulation->philosophers[i]))
			return (true);
		if (simulation->must_eat_count != -1)
			if (simulation->philosophers[i]->times_ate
				< (unsigned int)simulation->must_eat_count)
				all_ate_enough = false;
		pthread_mutex_unlock(&simulation->philosophers[i]->meal_time_lock);
		i++;
	}
	if (simulation->must_eat_count != -1 && all_ate_enough == true)
	{
		set_sim_stop_flag(simulation, true);
		return (true);
	}
	return (false);
}

/* grim_reaper:
*	The grim reaper thread's routine. Checks if a philosopher must
*	be killed and if all philosophers ate enough. If one of those two
*	end conditions are reached, it stops the simulation.
*/
void	*grim_reaper(void *data)
{
	t_simulation			*simulation;

	simulation = (t_simulation *)data;
	if (simulation->must_eat_count == 0)
		return (NULL);
	set_sim_stop_flag(simulation, false);
	sim_start_delay(simulation->start_time);
	while (true)
	{
		if (end_condition_reached(simulation) == true)
			return (NULL);
		usleep(1000);
	}
	return (NULL);
}

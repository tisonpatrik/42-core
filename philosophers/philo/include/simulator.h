#ifndef SIMULATOR_H
#define SIMULATOR_H

# include <pthread.h>
# include <limits.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <stdbool.h>

/******************************************************************************
*                                     Macros                                  *
******************************************************************************/

# define MAX_PHILOS	250
# define STR_MAX_PHILOS "250"

# define STR_ERR_INPUT_DIGIT	"%s invalid input: %s: \
not a valid unsigned integer between 0 and 2147483647.\n"
# define STR_ERR_INPUT_POFLOW	"%s invalid input: \
there must be between 1 and %s philosophers.\n"
# define STR_ERR_THREAD	"%s error: Could not create thread.\n"
# define STR_ERR_MALLOC	"%s error: Could not allocate memory.\n"
# define STR_ERR_MUTEX	"%s error: Could not create mutex.\n"

# define DEBUG_FORMATTING 0

/******************************************************************************
*                                 Structures                                  *
******************************************************************************/

typedef struct s_philo	t_philosopher;

typedef struct s_inputs
{
	int				nb_philos;
	time_t			time_to_die;
	time_t			time_to_eat;
	time_t			time_to_sleep;
	int				must_eat_count;
}	t_inputs;

typedef struct s_parsed
{
	t_inputs	inputs;
	char		*error;
}	t_parsed;

typedef struct s_simulation
{
	time_t			start_time;
	unsigned int	nb_philos;
	pthread_t		grim_reaper;
	time_t			time_to_die;
	time_t			time_to_eat;
	time_t			time_to_sleep;
	int				must_eat_count;
	bool			sim_stop;
	pthread_mutex_t	sim_stop_lock;
	pthread_mutex_t	write_lock;
	pthread_mutex_t	*fork_locks;
	t_philosopher			**philosophers;
}	t_simulation;

typedef struct s_result
{
	t_simulation	*simulation;
	char			*error;
}	t_result;

typedef struct s_philo
{
	pthread_t			thread;
	unsigned int		id;
	unsigned int		times_ate;

	unsigned int        left_fork;
	unsigned int        right_fork;
	pthread_mutex_t		meal_time_lock;
	time_t				last_meal;
	t_simulation				*simulation;
}	t_philosopher;

typedef enum e_status
{
	DIED = 0,
	EATING = 1,
	SLEEPING = 2,
	THINKING = 3,
	GOT_FORK_1 = 4,
	GOT_FORK_2 = 5
}	t_status;

/******************************************************************************
*                           Function Prototypes                               *
******************************************************************************/


char	*start_simulation(t_simulation *simulation);
void	stop_simulation(t_simulation	*table);

//	validator.c
t_parsed		inputs_validator(int ac, char **av);
bool			is_valid_input(int ac, char **av);

//	atoi.c
int				integer_atoi(char *str);

//	arena.c
t_result				create_simulation(t_inputs inputs);

//	routines.c
void			*philosopher(void *data);

//	time.c
time_t			get_time_in_ms(void);
void			philo_sleep(t_simulation *table, time_t sleep_time);
void			sim_start_delay(time_t start_time);

//	output.c
void			write_status(t_philosopher *philo, bool reaper, t_status status);
void			write_outcome(t_simulation *table);
int				msg(char *str, char *detail, int exit_no);

//	grim_reaper.c
void			*grim_reaper(void *data);
bool			has_simulation_stopped(t_simulation *table);

//	arena.c
void			destroy_simulation(t_simulation *simulation);


#endif

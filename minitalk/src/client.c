/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptison <ptison@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 21:14:51 by ptison            #+#    #+#             */
/*   Updated: 2025/09/24 14:58:35 by ptison           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minitalk.h"

int			g_confirm_flag = 0;

static void	signal_handler(int sig)
{
	g_confirm_flag = 1;
	(void)sig;
}

static void	send_bit(int pid, int bit)
{
	int	signal;

	if (bit == 1)
		signal = SIGUSR1;
	else
		signal = SIGUSR2;
	if (kill(pid, signal) == -1)
	{
		ft_putstr_fd("Error", 2);
		exit(EXIT_FAILURE);
	}
	while (!g_confirm_flag)
		;
	g_confirm_flag = 0;
}

static void	send_message(pid_t pid, char *message)
{
	int	i;
	int	j;

	i = 0;
	while (message[i])
	{
		j = 7;
		while (j >= 0)
		{
			send_bit(pid, (message[i] >> i) & 1);
			usleep(400);
			j--;
		}
		i++;
	}
}

int	main(int argc, char **argv)
{
	t_pid	pid;

	if (argc < 3)
	{
		exit(EXIT_FAILURE);
	}
	pid = ft_atoi(argv[1]);
	if (pid < 1)
	{
		exit(EXIT_FAILURE);
	}
	signal(SIGUSR2, signal_handler);
	send_message(pid, argv[2]);
	return (EXIT_SUCCESS);
}

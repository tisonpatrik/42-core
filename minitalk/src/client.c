/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptison <ptison@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 21:14:51 by ptison            #+#    #+#             */
/*   Updated: 2025/09/24 15:56:21 by ptison           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minitalk.h"

static void	signal_handler(int sig)
{
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
	pause();
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
			send_bit(pid, (message[i] >> j) & 1);
			j--;
		}
		i++;
	}
}

int	main(int argc, char **argv)
{
	pid_t				pid;
	struct sigaction	sa;

	if (argc < 3)
		exit(EXIT_FAILURE);
	pid = ft_atoi(argv[1]);
	if (pid < 1)
		exit(EXIT_FAILURE);
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	sa.sa_handler = signal_handler;
	sigaction(SIGUSR2, &sa, NULL);
	send_message(pid, argv[2]);
	return (EXIT_SUCCESS);
}

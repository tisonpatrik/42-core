/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptison <ptison@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 21:14:51 by ptison            #+#    #+#             */
/*   Updated: 2025/09/25 10:30:40 by ptison           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minitalk.h"


static volatile sig_atomic_t	g_ack = 0;

static void	ack_handler(int sig)
{
	(void)sig;
	g_ack = 1;
}

static void	send_bit(pid_t pid, int bit)
{
	int	s = bit ? SIGUSR1 : SIGUSR2;

	if (kill(pid, s) == -1)
	{
		ft_putstr_fd("Error", 2);
		exit(EXIT_FAILURE);
	}
	while (!g_ack)
		pause();
	g_ack = 0;
}

static void	send_byte(pid_t pid, unsigned char uc)
{
	for (int j = 7; j >= 0; --j)
		send_bit(pid, (uc >> j) & 1);
}

static void	send_message(pid_t pid, const char *message)
{
	for (int i = 0; message[i]; ++i)
		send_byte(pid, (unsigned char)message[i]);
	send_byte(pid, '\0');
}

int	main(int argc, char **argv)
{
	if (argc < 3)
		exit(EXIT_FAILURE);

	pid_t pid = (pid_t)ft_atoi(argv[1]);
	if (pid < 1)
		exit(EXIT_FAILURE);

	struct sigaction	sa;

	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	sa.sa_handler = ack_handler;
	sigaction(SIGUSR2, &sa, NULL);

	send_message(pid, argv[2]);
	return (EXIT_SUCCESS);
}

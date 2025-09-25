/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptison <ptison@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 20:52:17 by ptison            #+#    #+#             */
/*   Updated: 2025/09/25 10:31:09 by ptison           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/include/libft.h"
#include <signal.h>
#include <unistd.h>

void	signal_handler(int signo, siginfo_t *info, void *context)
{
	static unsigned char	data = 0;
	static char				nbits = 0;
	pid_t					pidof_sender;

	(void)context;
	pidof_sender = info->si_pid;
	if (signo == SIGUSR1)
		data |= 1 << (7 - nbits++);
	if (signo == SIGUSR2)
		nbits++;
	if (nbits == 8)
	{
		write(STDOUT_FILENO, &data, 1);
		nbits = 0;
		data = 0;
	}
	kill(pidof_sender, SIGUSR1);
}

int	main(void)
{
	struct sigaction	sa_action;

	ft_printf("%d",getpid());
	sa_action.sa_flags = SA_SIGINFO;
	sa_action.sa_sigaction = signal_handler;
	sigemptyset(&sa_action.sa_mask);
	sigaction(SIGUSR1, &sa_action, NULL);
	sigaction(SIGUSR2, &sa_action, NULL);
	while (1)
	{
		pause();
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptison <ptison@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 20:52:17 by ptison            #+#    #+#             */
/*   Updated: 2025/09/27 11:38:24 by ptison           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/include/libft.h"
#include <signal.h>
#include <unistd.h>

void	signal_handler(int signo, siginfo_t *info, void *ctx)
{
	static unsigned char	data = 0;
	static char				nbits = 0;
	int						bit_position;
	int						mask;

	(void)ctx;
	if (signo == SIGUSR1)
	{
		bit_position = 7 - nbits;
		mask = 1 << bit_position;
		data = data | mask;
		nbits++;
	}
	else if (signo == SIGUSR2)
	{
		nbits++;
	}
	if (nbits == 8)
	{
		write(STDOUT_FILENO, &data, 1);
		nbits = 0;
		data = 0;
	}
	kill(info->si_pid, SIGUSR1);
}

int	main(void)
{
	struct sigaction	sa_action;

	ft_printf("%d \n", getpid());
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

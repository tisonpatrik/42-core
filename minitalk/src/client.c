/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptison <ptison@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 21:14:51 by ptison            #+#    #+#             */
/*   Updated: 2025/09/27 11:38:35 by ptison           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/include/libft.h"
#include <signal.h>
#include <unistd.h>

void	signal_handler(int sig)
{
	(void)sig;
}

void	send_char_bits(pid_t pid, char c)
{
	int	i;
	int	bit;

	i = 0;
	while (i < 8)
	{
		bit = (c >> (7 - i)) & 1;
		if (bit == 1)
			kill(pid, SIGUSR1);
		else
			kill(pid, SIGUSR2);
		i++;
		usleep(700);
	}
}

void	send_message(pid_t pid, char *message)
{
	int	i;

	i = 0;
	while (message[i] != '\0')
	{
		send_char_bits(pid, message[i]);
		i++;
	}
	send_char_bits(pid, '\n');
}

int	main(int argc, char *argv[])
{
	pid_t	pid;

	if (argc != 3)
	{
		return (1);
	}
	pid = ft_atoi(argv[1]);
	signal(SIGUSR1, &signal_handler);
	signal(SIGUSR2, &signal_handler);
	if (pid <= 0)
	{
		return (1);
	}
	send_message(pid, argv[2]);
	return (0);
}

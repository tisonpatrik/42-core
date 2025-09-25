/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptison <ptison@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 21:14:51 by ptison            #+#    #+#             */
/*   Updated: 2025/09/25 11:41:02 by ptison           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/include/libft.h"
#include <signal.h>
#include <unistd.h>

void	signal_handler(int sig)
{
	(void)sig;
}

void	encode_char(pid_t pid, char c)
{
	int	i;

	i = 0;
	while (i < 8)
	{
		if (c & (1 << (7 - i)))
			kill(pid, SIGUSR1);
		else
			kill(pid, SIGUSR2);
		i++;
		usleep(1000);
	}
}

int	main(int argc, char *argv[])
{
	pid_t	pid;
	int	i;

	i = 0;
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
	while (argv[2][i] != '\0')
		encode_char(pid, argv[2][i++]);
	encode_char(pid, '\n');
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omaly <student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/26 12:40:20 by omaly             #+#    #+#             */
/*   Updated: 2026/03/04 16:56:18 by omaly            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	main(int argc, char **argv, char **envp)
{
	t_shell	shell;
	char	*line;

	(void)argc;
	(void)argv;
	if (shell_init(&shell, envp) != SUCCESS)
		return (1);
	while (1)
	{
		line = shell_get_input();
		if (!line)
		{
			if (isatty(STDIN_FILENO))
				ft_putstr_fd("exit\n", STDERR_FILENO);
			break ;
		}
		if (!shell_process_line(&shell, line))
		{
			free(line);
			break ;
		}
		free(line);
	}
	shell_cleanup(&shell);
	return (shell.exit_code);
}

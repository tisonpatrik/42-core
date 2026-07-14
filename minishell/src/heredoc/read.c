/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omaly <student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/26 12:37:07 by omaly             #+#    #+#             */
/*   Updated: 2026/03/04 16:29:35 by omaly            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/heredoc.h"

static bool	check_eof(char *line)
{
	if (!line)
	{
		ft_putstr_fd("bash: warning: here-document delimited by end-of-file\n",
			2);
		return (true);
	}
	return (false);
}

static bool	process_line(t_hdoc_ctx *ctx, t_str8 delim, bool expand, char *line)
{
	t_str8	view;

	view = ft_str8_from_cstr(line);
	if (ft_str8_match(view, delim))
		return (false);
	if (expand)
		heredoc_write_expanded(ctx, line);
	else
	{
		hdoc_write(ctx->fd, view);
		hdoc_write(ctx->fd, ft_str8_from_cstr("\n"));
	}
	return (true);
}

static void	strip_newline(char *line)
{
	char	*newline_pos;

	if (!line)
		return ;
	newline_pos = ft_strchr(line, '\n');
	if (newline_pos)
		*newline_pos = '\0';
}

static void	heredoc_child_routine(t_hdoc_ctx *ctx, t_str8 delim, bool expand)
{
	char	*line;
	bool	keep_reading;

	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_IGN);
	keep_reading = true;
	while (keep_reading)
	{
		if (isatty(STDIN_FILENO))
		{
			line = readline("> ");
		}
		else
		{
			line = ft_get_line(STDIN_FILENO);
			strip_newline(line);
		}
		if (check_eof(line))
			break ;
		keep_reading = process_line(ctx, delim, expand, line);
		free(line);
	}
	close(ctx->fd);
	exit(E_SUCCESS);
}

bool	heredoc_process_file(t_hdoc_ctx *ctx, char *filename, t_str8 delim,
		bool expand)
{
	int		fd;
	pid_t	pid;
	int		status;

	fd = open(filename, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd == -1)
	{
		shell_perror("heredoc", filename);
		return (false);
	}
	ctx->fd = fd;
	pid = fork();
	if (pid == -1)
	{
		close(fd);
		return (false);
	}
	if (pid == 0)
		heredoc_child_routine(ctx, delim, expand);
	close(fd);
	waitpid(pid, &status, 0);
	if (WIFSIGNALED(status) && WTERMSIG(status) == SIGINT)
		return (write(1, "\n", 1), false);
	return (true);
}

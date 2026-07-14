/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omaly <student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/26 12:35:54 by omaly             #+#    #+#             */
/*   Updated: 2026/03/04 16:48:17 by omaly            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/execution.h"

static int	get_flags(t_token_type type)
{
	if (type == TOKEN_REDIRECT_APPEND)
		return (O_WRONLY | O_CREAT | O_APPEND);
	return (O_WRONLY | O_CREAT | O_TRUNC);
}

static int	get_target_fd(t_token_type type)
{
	if (type == TOKEN_REDIRECT_INPUT || type == TOKEN_REDIRECT_HEREDOC)
		return (STDIN_FILENO);
	if (type == TOKEN_REDIRECT_ERR)
		return (STDERR_FILENO);
	return (STDOUT_FILENO);
}

static int	open_redir(t_arena *arena, t_token *tok)
{
	char	*path;

	if (!tok->value.str)
		return (-1);
	path = str8_to_cstr(arena, tok->value);
	if (!path)
		return (-1);
	if (tok->type == TOKEN_REDIRECT_INPUT
		|| tok->type == TOKEN_REDIRECT_HEREDOC)
		return (open(path, O_RDONLY));
	return (open(path, get_flags(tok->type), 0644));
}

bool	exec_handle_redirs(t_arena *arena, t_token *redirs)
{
	int	fd;
	int	target;

	while (redirs)
	{
		fd = open_redir(arena, redirs);
		if (fd == -1)
		{
			if (redirs->value.str)
				shell_perror(NULL, (char *)redirs->value.str);
			return (false);
		}
		target = get_target_fd(redirs->type);
		if (dup2(fd, target) == -1)
		{
			if (fd != target)
				close(fd);
			return (false);
		}
		if (fd != target)
			close(fd);
		redirs = redirs->next;
	}
	return (true);
}

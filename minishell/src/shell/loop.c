/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omaly <student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/26 12:39:12 by omaly             #+#    #+#             */
/*   Updated: 2026/03/04 16:56:09 by omaly            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static bool	is_empty_input(const char *line)
{
	size_t	i;

	if (!line || !*line)
		return (true);
	i = 0;
	while (line[i])
	{
		if (!ft_isspace(line[i]))
			return (false);
		i++;
	}
	return (true);
}

static bool	handle_syntax_error(t_shell *shell)
{
	ft_putstr_fd("minishell: syntax error\n", STDERR_FILENO);
	shell->exit_code = 2;
	return (isatty(STDIN_FILENO));
}

static bool	run_heredoc_phase(t_shell *shell, t_ast_node *ast)
{
	t_hdoc_ctx	ctx;

	ctx.arena = shell->cmd_arena;
	ctx.env_list = shell->env_list;
	ctx.last_exit_code = shell->exit_code;
	if (!process_heredocs(&ctx, ast))
	{
		shell->exit_code = 130;
		return (false);
	}
	return (true);
}

bool	shell_process_line(t_shell *shell, char *line)
{
	t_token		*tokens;
	t_ast_node	*ast;
	bool		cont;

	if (is_empty_input(line))
		return (true);
	add_history(line);
	ast = NULL;
	cont = true;
	tokens = lexer_build_token_list(shell->cmd_arena, line);
	if (tokens)
		ast = parser_build_ast(shell->cmd_arena, tokens);
	if (!tokens || !ast)
		cont = handle_syntax_error(shell);
	else if (run_heredoc_phase(shell, ast))
	{
		expand_ast(shell, ast);
		shell->exit_code = executor(shell, ast);
	}
	heredoc_cleanup(ast);
	ft_arena_reset(shell->cmd_arena);
	return (cont);
}

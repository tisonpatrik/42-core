/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omaly <student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/26 12:31:21 by omaly             #+#    #+#             */
/*   Updated: 2026/02/26 12:31:26 by omaly            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "builtins.h"
# include "execution.h"
# include "expander.h"
# include "heredoc.h"
# include "parser.h"
# include "state.h"
# include "types.h"
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

# define CMD_ARENA_SIZE 10485760
# define LIFE_ARENA_SIZE 10485760

t_status	shell_init(t_shell *shell, char **envp);
void		shell_cleanup(t_shell *shell);
char		*shell_get_input(void);
bool		shell_process_line(t_shell *shell, char *line);

#endif

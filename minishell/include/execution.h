/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omaly <student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/26 12:31:36 by omaly             #+#    #+#             */
/*   Updated: 2026/02/26 12:31:37 by omaly            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H

# include "../libft/include/libft.h"
# include "builtins.h"
# include "parser.h"
# include "state.h"
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/stat.h>
# include <unistd.h>
# include <wait.h>

int		executor(t_shell *shell, t_ast_node *node);
int		exec_pipe(t_shell *shell, t_ast_node *node);
int		exec_simple_cmd(t_shell *shell, t_ast_node *node);
bool	exec_handle_redirs(t_arena *arena, t_token *redirs);
char	**exec_args_to_array(t_arena *arena, t_str8 *args);
void	exec_child_routine(t_shell *shell, t_ast_node *node);
char	*exec_find_path(t_shell *shell, char *cmd);

#endif

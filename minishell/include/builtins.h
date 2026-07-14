/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omaly <student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/26 12:31:48 by omaly             #+#    #+#             */
/*   Updated: 2026/03/04 17:01:12 by omaly            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include "../libft/include/libft.h"
# include "error.h"
# include "state.h"
# include "types.h"
# include <stdio.h>
# include <unistd.h>

t_builtin_id	identify_builtin(char *cmd);
t_status		run_builtin(t_shell *shell, t_builtin_id id, char **args);
t_status		ft_echo(char **args);
t_status		ft_cd(t_shell *shell, char **args);
t_status		ft_pwd(void);
t_status		ft_export(t_shell *shell, char **args);
t_status		ft_unset(t_shell *shell, char **args);
t_status		ft_exit(t_shell *shell, char **args);
t_status		ft_env(t_shell *shell, char **args);
void			print_env_arr(t_env **arr, size_t count);
t_status		process_export_arg(t_shell *shell, char *arg_str);
t_status		handle_assign(t_shell *shell, t_str8 arg, char *arg_str,
					char *eq_sign);
t_status		handle_append(t_shell *shell, t_str8 arg, char *arg_str,
					char *app_sign);

#endif

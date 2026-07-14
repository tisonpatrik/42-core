/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   state.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omaly <student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/26 12:32:19 by omaly             #+#    #+#             */
/*   Updated: 2026/03/04 16:57:06 by omaly            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STATE_H
# define STATE_H

# include "../libft/include/libft.h"
# include "types.h"
# include <stdio.h>
# include <readline/readline.h>
# include <signal.h>
# include <unistd.h>

t_status	env_init(t_shell *shell, char **envp);
t_env		*env_new(t_arena *arena, t_str8 key, t_str8 value);
t_status	env_add_back(t_env **head, t_env *new_node);
t_status	env_set(t_shell *shell, t_str8 key, t_str8 value);
t_status	env_remove(t_shell *shell, t_str8 key);

t_str8		env_get(t_env *env, t_str8 key);
char		**env_to_array(t_shell *shell);

void		setup_signals_interactive(void);
void		handle_sigint(int sig);

void		setup_signals_blocking(void);
void		setup_signals_child(void);

#endif

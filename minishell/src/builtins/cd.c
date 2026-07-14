/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omaly <student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/26 12:34:32 by omaly             #+#    #+#             */
/*   Updated: 2026/03/04 16:28:16 by omaly            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/builtins.h"

static char	*get_target_path(t_shell *shell, char *arg)
{
	t_str8	var;

	if (!arg || (arg[0] == '-' && arg[1] == '-' && arg[2] == '\0'))
	{
		var = env_get(shell->env_list, ft_str8_from_cstr("HOME"));
		if (!var.str)
			return (shell_error("cd", NULL, "HOME not set"), NULL);
		return ((char *)var.str);
	}
	if (arg[0] == '-' && arg[1] == '\0')
	{
		var = env_get(shell->env_list, ft_str8_from_cstr("OLDPWD"));
		if (!var.str)
			return (shell_error("cd", NULL, "OLDPWD not set"), NULL);
		ft_putstr_fd((char *)var.str, STDOUT_FILENO);
		ft_putstr_fd("\n", STDOUT_FILENO);
		return ((char *)var.str);
	}
	return (arg);
}

static void	update_pwd_vars(t_shell *shell, t_str8 old_pwd)
{
	char	new_pwd[4096];

	if (old_pwd.str)
		env_set(shell, ft_str8_from_cstr("OLDPWD"), old_pwd);
	else
		env_remove(shell, ft_str8_from_cstr("OLDPWD"));
	if (getcwd(new_pwd, sizeof(new_pwd)))
		env_set(shell, ft_str8_from_cstr("PWD"), ft_str8_from_cstr(new_pwd));
	else
	{
		ft_putstr_fd("cd: error retrieving current directory: "
			"getcwd: cannot access parent directories: "
			"No such file or directory\n",
			STDERR_FILENO);
	}
}

t_status	ft_cd(t_shell *shell, char **args)
{
	char	*path;
	t_str8	old_pwd;
	t_str8	old_copy;

	if (args[1] && args[2])
	{
		shell_error("cd", NULL, "too many arguments");
		return (2);
	}
	path = get_target_path(shell, args[1]);
	if (!path)
		return (FAILURE);
	old_pwd = env_get(shell->env_list, ft_str8_from_cstr("PWD"));
	old_copy = (t_str8){NULL, 0};
	if (old_pwd.str)
		old_copy = ft_str8_dup(shell->cmd_arena, old_pwd);
	if (chdir(path) != 0)
	{
		shell_perror("cd", path);
		return (FAILURE);
	}
	update_pwd_vars(shell, old_copy);
	return (SUCCESS);
}

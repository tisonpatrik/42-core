/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omaly <student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/26 12:36:01 by omaly             #+#    #+#             */
/*   Updated: 2026/03/04 16:29:03 by omaly            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/execution.h"

static char	*build_candidate(t_arena *arena, char *dir, int dir_len, char *cmd)
{
	char	*res;
	int		cmd_len;

	cmd_len = ft_strlen(cmd);
	res = ft_arena_push(arena, dir_len + 1 + cmd_len + 1);
	if (!res)
		return (NULL);
	ft_memcpy(res, dir, dir_len);
	res[dir_len] = '/';
	ft_memcpy(res + dir_len + 1, cmd, cmd_len + 1);
	return (res);
}

static char	*search_in_path(t_shell *shell, char *path_var, char *cmd)
{
	char	*cursor;
	char	*end;
	char	*candidate;

	cursor = path_var;
	while (*cursor)
	{
		end = ft_strchr(cursor, ':');
		if (!end)
			end = cursor + ft_strlen(cursor);
		if (end == cursor)
			candidate = build_candidate(shell->cmd_arena, ".", 1, cmd);
		else
			candidate = build_candidate(shell->cmd_arena, cursor, end - cursor,
					cmd);
		if (candidate && access(candidate, X_OK) == 0)
			return (candidate);
		if (*end == '\0')
			break ;
		cursor = end + 1;
	}
	return (NULL);
}

char	*exec_find_path(t_shell *shell, char *cmd)
{
	char	*path_var;

	if (!cmd || !*cmd)
		return (NULL);
	if (ft_strchr(cmd, '/'))
		return (str8_to_cstr(shell->cmd_arena, ft_str8_from_cstr(cmd)));
	path_var = (char *)env_get(shell->env_list, ft_str8_from_cstr("PATH")).str;
	if (!path_var)
		return (NULL);
	return (search_in_path(shell, path_var, cmd));
}

char	**exec_args_to_array(t_arena *arena, t_str8 *args)
{
	int		count;
	char	**arr;
	int		i;

	if (!args)
		return (NULL);
	count = 0;
	while (args[count].str)
		count++;
	arr = ft_arena_push(arena, sizeof(char *) * (count + 1));
	if (!arr)
		return (NULL);
	i = 0;
	while (i < count)
	{
		arr[i] = str8_to_cstr(arena, args[i]);
		i++;
	}
	arr[i] = NULL;
	return (arr);
}

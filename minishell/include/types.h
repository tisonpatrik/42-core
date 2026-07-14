/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   types.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omaly <student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/26 12:32:38 by omaly             #+#    #+#             */
/*   Updated: 2026/02/26 12:32:43 by omaly            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TYPES_H
# define TYPES_H

# include "../libft/include/libft.h"
# include <stdbool.h>
# include <stddef.h>

typedef struct s_arena	t_arena;

typedef struct s_env
{
	t_str8				key;
	t_str8				value;
	struct s_env		*next;
}						t_env;

typedef struct s_shell
{
	t_env				*env_list;
	int					exit_code;
	t_arena				*life_arena;
	t_arena				*cmd_arena;
}						t_shell;

typedef enum e_node_type
{
	NODE_COMMAND,
	NODE_PIPE
}						t_node_type;

typedef enum e_builtin_id
{
	BUILTIN_NONE = 0,
	BUILTIN_ECHO,
	BUILTIN_CD,
	BUILTIN_PWD,
	BUILTIN_EXPORT,
	BUILTIN_UNSET,
	BUILTIN_ENV,
	BUILTIN_EXIT
}						t_builtin_id;

typedef enum e_status
{
	SUCCESS = 0,
	FAILURE = 1,
	ERR_USAGE = 2,
	ERR_NO_CMD = 127,
	ERR_NO_PERM = 126
}						t_status;

#endif

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omaly <student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/26 12:32:03 by omaly             #+#    #+#             */
/*   Updated: 2026/03/04 16:56:52 by omaly            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEREDOC_H
# define HEREDOC_H

# include "../libft/include/libft.h"
# include "builtins.h"
# include "parser.h"
# include <fcntl.h>
# include <sys/wait.h>

# define E_SUCCESS 0
# define E_GENERAL 1
# define E_SIGINT 13

typedef struct s_hdoc_ctx
{
	t_arena	*arena;
	t_env	*env_list;
	int		last_exit_code;
	int		fd;
}			t_hdoc_ctx;

bool		process_heredocs(t_hdoc_ctx *ctx, t_ast_node *node);
bool		heredoc_process_file(t_hdoc_ctx *ctx, char *filename, t_str8 delim,
				bool expand);
void		heredoc_write_expanded(t_hdoc_ctx *ctx, char *line);
t_str8		heredoc_strip_quotes(t_arena *arena, t_str8 raw, bool *expand);
t_str8		heredoc_generate_name(t_arena *arena, int id);
bool		hdoc_write(int fd, t_str8 s);
void		write_exit_code(t_hdoc_ctx *ctx);
void		heredoc_cleanup(t_ast_node *node);

#endif

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omaly <student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/26 12:31:15 by omaly             #+#    #+#             */
/*   Updated: 2026/02/26 12:31:16 by omaly            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# include "../libft/include/libft.h"
# include "error.h"

typedef enum e_token_type
{
	TOKEN_WORD,
	TOKEN_PIPE,
	TOKEN_REDIRECT_INPUT,
	TOKEN_REDIRECT_OUTPUT,
	TOKEN_REDIRECT_APPEND,
	TOKEN_REDIRECT_HEREDOC,
	TOKEN_REDIRECT_ERR,
	TOKEN_ERROR,
	TOKEN_EOF
}					t_token_type;

typedef struct s_token
{
	t_str8			value;
	t_token_type	type;
	struct s_token	*next;
}					t_token;

typedef struct s_lex_ctx
{
	t_arena			*arena;
	t_token			*head;
	t_token			*last;
	t_str8			input;
	size_t			i;
}					t_lex_ctx;

t_token				*lexer_build_token_list(t_arena *arena, char *line);
t_token_type		scan_token_type(const char *line, size_t *len);
t_token				*token_create(t_arena *arena, t_str8 value,
						t_token_type type);
void				token_add_back(t_token **list, t_token *new_tok);

#endif

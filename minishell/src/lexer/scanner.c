/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scanner.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omaly <student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/26 12:37:39 by omaly             #+#    #+#             */
/*   Updated: 2026/03/04 16:47:55 by omaly            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/lexer.h"

bool	is_metachar(char c)
{
	return (c == '<' || c == '>' || c == '|');
}

static bool	skip_quoted_part(const char *line, size_t *i)
{
	char	quote;

	quote = line[*i];
	(*i)++;
	while (line[*i] && line[*i] != quote)
		(*i)++;
	if (!line[*i])
		return (false);
	(*i)++;
	return (true);
}

static t_token_type	scan_redir_type(const char *s, size_t *len)
{
	if (s[0] == '2' && s[1] == '>')
		return (*len = 2, TOKEN_REDIRECT_ERR);
	if (s[0] == '>')
	{
		if (s[1] == '|')
			return (*len = 2, TOKEN_REDIRECT_OUTPUT);
		if (s[1] == '>')
			return (*len = 2, TOKEN_REDIRECT_APPEND);
		return (*len = 1, TOKEN_REDIRECT_OUTPUT);
	}
	if (s[0] == '<')
	{
		if (s[1] == '<')
			return (*len = 2, TOKEN_REDIRECT_HEREDOC);
		return (*len = 1, TOKEN_REDIRECT_INPUT);
	}
	return (TOKEN_ERROR);
}

static t_token_type	scan_word_chunk(const char *line, size_t *len)
{
	size_t	i;

	i = 0;
	while (line[i])
	{
		if (line[i] == '\'' || line[i] == '\"')
		{
			if (!skip_quoted_part(line, &i))
				return (TOKEN_ERROR);
		}
		else if (is_metachar(line[i]) || ft_isspace(line[i]))
			break ;
		else
			i++;
	}
	*len = i;
	if (i == 0)
		return (TOKEN_ERROR);
	return (TOKEN_WORD);
}

t_token_type	scan_token_type(const char *line, size_t *len)
{
	if (line[0] == '|')
	{
		*len = 1;
		return (TOKEN_PIPE);
	}
	if (line[0] == '<' || line[0] == '>' || (line[0] == '2' && line[1] == '>'))
		return (scan_redir_type(line, len));
	return (scan_word_chunk(line, len));
}

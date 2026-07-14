/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   core_helpers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omaly <student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/04 16:46:03 by omaly             #+#    #+#             */
/*   Updated: 2026/03/04 16:47:32 by omaly            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/expander.h"

char	*find_var_end(char *start)
{
	if (*start == '?')
		return (start + 1);
	if (ft_isdigit(*start))
		return (start + 1);
	while (*start && (ft_isalnum(*start) || *start == '_'))
		start++;
	return (start);
}

void	flush_current_word(t_exp_ctx *ctx)
{
	if (ctx->builder.total_size > 0 || ctx->was_quoted)
	{
		exp_builder_append(ctx->arena, &ctx->expanded_words,
			exp_builder_flatten(ctx->arena, &ctx->builder));
		ctx->builder = (t_str8_list){0};
		ctx->was_quoted = false;
	}
}

void	process_dollar_split(t_exp_ctx *ctx, t_str8 val)
{
	size_t	i;
	size_t	start;

	i = 0;
	while (i < val.len)
	{
		if (ft_isspace(val.str[i]))
		{
			flush_current_word(ctx);
			while (i < val.len && ft_isspace(val.str[i]))
				i++;
		}
		else
		{
			start = i;
			while (i < val.len && !ft_isspace(val.str[i]))
				i++;
			exp_builder_append(ctx->arena, &ctx->builder, ft_str8_substr(val,
					start, i - start));
		}
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vars.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omaly <student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/26 12:36:35 by omaly             #+#    #+#             */
/*   Updated: 2026/02/26 12:36:39 by omaly            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/expander.h"

t_str8	exp_get_var_val(t_exp_ctx *ctx, t_str8 key)
{
	char	*code_str;
	t_str8	val;

	if (ft_str8_match(key, ft_str8_from_cstr("?")))
	{
		code_str = ft_itoa(ctx->exit_code);
		if (!code_str)
			return (ft_str8_from_cstr(""));
		val = ft_str8_dup(ctx->arena, ft_str8_from_cstr(code_str));
		free(code_str);
		return (val);
	}
	val = env_get(ctx->env_list, key);
	if (!val.str)
		return (ft_str8_from_cstr(""));
	return (val);
}

t_str8	exp_handle_tilde(t_exp_ctx *ctx, t_str8 word)
{
	t_str8	home;
	t_str8	rest;

	if (word.len == 0 || word.str[0] != '~')
		return (word);
	if (word.len > 1 && word.str[1] != '/')
		return (word);
	home = env_get(ctx->env_list, ft_str8_from_cstr("HOME"));
	if (!home.str)
		return (word);
	if (word.len == 1)
		return (home);
	rest = ft_str8_substr(word, 1, word.len - 1);
	return (ft_str8_join(ctx->arena, home, rest));
}

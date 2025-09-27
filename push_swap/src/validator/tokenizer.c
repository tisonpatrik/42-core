/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptison <ptison@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 21:17:51 by ptison            #+#    #+#             */
/*   Updated: 2025/09/27 11:37:29 by ptison           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/validator.h"
#include <errno.h>

int	count_parts(char **parts)
{
	int	j;
	int	count;

	j = 0;
	count = 0;
	if (!parts)
		fatal_cleanup_and_exit(NULL, NULL);
	while (parts[j])
	{
		if (parts[j][0] == '\0')
			fatal_cleanup_and_exit(NULL, parts);
		count++;
		j++;
	}
	return (count);
}

void	store_token(const char *tok, int *out, int *out_index,
		char **parts_for_cleanup)
{
	char	*endptr;
	int		val;

	endptr = NULL;
	if (!tok || tok[0] == '\0')
		fatal_cleanup_and_exit(out, parts_for_cleanup);
	errno = 0;
	val = ft_strtoi10(tok, &endptr);
	if (*endptr != '\0' || errno == ERANGE)
		fatal_cleanup_and_exit(out, parts_for_cleanup);
	out[(*out_index)++] = val;
}

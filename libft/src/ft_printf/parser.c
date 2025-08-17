/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptison <ptison@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 14:04:31 by ptison            #+#    #+#             */
/*   Updated: 2025/08/17 11:00:25 by ptison           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char	parse_format(const char *format, int *i)
{
	char	type;

	type = format[*i];
	if (type == 'c' || type == 's' || type == 'p' || type == 'd' || type == 'i'
		|| type == 'u' || type == 'x' || type == 'X' || type == '%')
	{
		(*i)++;
		return (type);
	}
	return (0);
}

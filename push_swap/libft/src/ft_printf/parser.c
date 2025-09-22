/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptison <ptison@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 21:12:25 by ptison            #+#    #+#             */
/*   Updated: 2025/09/22 18:29:50 by ptison           ###   ########.fr       */
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

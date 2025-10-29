/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strspn.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptison <ptison@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/29 17:11:05 by ptison            #+#    #+#             */
/*   Updated: 2025/10/29 17:16:14 by ptison           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>

bool	is_accepted(char c, const char *accept)
{
	int		i;
	bool	is_here;

	i = 0;
	is_here = false;
	while (accept[i])
	{
		if (c == accept[i])
		{
			is_here = true;
		}
		i++;
	}
	return (is_here);
}

size_t	ft_strspn(const char *s, const char *accept)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (is_accepted(s[i], accept))
		{
			i++;
		}
		else
		{
			return (i);
		}
	}
	return (i);
}

int	main(int ac, char **av)
{
	const char	*string;
	const char	*accept;
	size_t		expected;
	size_t		current;

	string = av[1];
	accept = av[2];
	expected = strspn(string, accept);
	current = ft_strspn(string, accept);
	printf("expected: %zu\n", expected);
	printf("current: %zu\n", current);
}

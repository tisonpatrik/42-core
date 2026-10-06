
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>

bool	is_rejected(char c, const char *reject)
{
	int		i;
	bool	is_here;

	i = 0;
	is_here = false;
	while (reject[i])
	{
		if (c == reject[i])
		{
			is_here = true;
		}
		i++;
	}
	return (is_here);
}

size_t	ft_strcspn(const char *s, const char *rejected)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (is_rejected(s[i], rejected))
		{
			return i;
		}
		else
		{
			i++;
		}
	}
	return (i);
}

int	main(int ac, char **av)
{
	const char	*string;
	const char	*rejected;
	size_t		expected;
	size_t		current;

	string = av[1];
	rejected = av[2];
	expected = strcspn(string, rejected);
	current = ft_strcspn(string, rejected);
	printf("expected: %zu\n", expected);
	printf("current: %zu\n", current);
}

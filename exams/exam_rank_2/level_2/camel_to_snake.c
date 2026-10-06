
#include <stdbool.h>
#include <unistd.h>

char	to_lower_case(char c)
{
	if (c >= 'A' && c <= 'Z')
	{
		return (c + 32);
	}
	return (-1);
}

int	main(int ac, char **av)
{
	char	*string;
	int		i;
	char	c;

	string = av[1];
	i = 0;
	while (string[i])
	{
		c = to_lower_case(string[i]);
		if (c > 0)
		{
			write(1, &"_", 1);
			write(1, &c, 1);
		}
		else
		{
			write(1, &string[i], 1);
		}
		i++;
	}
	write(1, &"\n", 1);
	return (0);
}

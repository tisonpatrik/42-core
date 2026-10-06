

#include <unistd.h>

char	get_transformation(char c)
{
	if (c >= 'A' && c <= 'Z')
	{
		return (((c - 'A' + 1) % 26) + 'A');
	}
	if (c >= 'a' && c <= 'z')
	{
		return (((c - 'a' + 1) % 26) + 'a');
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
		c = get_transformation(string[i]);
		if (c > 0)
			write(1, &c, 1);
		else
			write(1, &string[i], 1);
		i++;
	}
	write(1, "\n", 1);
	return (0);
}

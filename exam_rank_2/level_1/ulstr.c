
#include <unistd.h>

char	get_converted(char c)
{
	if (c >= 'A' && c <= 'Z')
		return (c + 32);
	if (c >= 'a' && c <= 'z')
		return (c - 32);
	return (c);
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
		c = get_converted(string[i]);
		write(1, &c, 1);
		i++;
	}
	write(1, "\n", 1);
	return (0);
}

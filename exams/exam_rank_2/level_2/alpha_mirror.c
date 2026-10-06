#include <unistd.h>

char	convert_character(char c)
{
	if (c >= 'A' && c <= 'Z')
		return ('Z' - (c - 'A'));
	if (c >= 'a' && c <= 'z')
		return ('z' - (c - 'a'));
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
		c = convert_character(string[i]);
		write(1, &c, 1);
		i++;
	}
	write(1, "\n", 1);
	return (0);
}

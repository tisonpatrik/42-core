
#include <unistd.h>

char	convert_by_thirteen(char c)
{
	if (c >= 'A' && c <= 'Z')
		return (((c - 'A' + 13) % 26) + 'A');
	if (c >= 'a' && c <= 'z')
		return (((c - 'a' + 13) % 26) + 'a');
	return (-1);
}

int	main(int ac, char **av)
{
	char	*string;
	int		i;
	int		converted;

	string = av[1];
	i = 0;
	while (string[i])
	{
		converted = convert_by_thirteen(string[i]);
		if (converted > 0)
			write(1, &converted, 1);
		else
			write(1, &string[i], 1);
		i++;
	}

	write(1, "\n", 1);
	return (0);
}

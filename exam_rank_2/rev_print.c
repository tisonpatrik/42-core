
#include <unistd.h>

int	main(int ac, char **av)
{
	char	*string;
	int		i;

	string = av[1];
	i = 0;
	while (string[i])
	{
		i++;
	}
	while (i >-1)
	{
		write(1, &string[i], 1);
		i--;
	}
	write(1, &"\n", 1);
	return (0);
}

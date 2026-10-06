
#include <unistd.h>

int	main(int ac, char **av)
{
	char	*string;
	char	*raw_source;
	char	*raw_target;
	char	src;
	char	target;
	int		i;

	string = av[1];
	raw_source = av[2];
	raw_target = av[3];
	src = raw_source[0];
	target = raw_target[0];
	i = 0;
	while (string[i])
	{
		if (string[i] == src)
			write(1, &target, 1);
		else
			write(1, &string[i], 1);
		i++;
	}
	write(1, "\n", 1);
	return (0);
}

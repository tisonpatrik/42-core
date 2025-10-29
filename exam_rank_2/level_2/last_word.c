#include <unistd.h>

int	get_len(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		i++;
	}
	return (i);
}

int	main(int ac, char **av)
{
	char	*str;
	int		end;
	int		start;

	if (ac != 2)
		return (0);
	str = av[1];
	end = get_len(str) - 1;
	while (end >= 0 && (str[end] == ' ' || str[end] == '\t'))
	{
		end--;
	}
	start = end;
	while (start >= 0 && !((str[start] == ' ' || str[start] == '\t')))
	{
		start--;
	}
	start++;
	while (start <= end)
	{
		write(1, &str[start], 1);
		start++;
	}
	write(1, "\n", 1);
	return (0);
}

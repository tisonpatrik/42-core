
#include <stdbool.h>
#include <unistd.h>

bool	is_space(char x)
{
	if ((x < '!') || (x > '~'))
	{
		return (true);
	}
	return (false);
}

int	get_start(char *string)
{
	int	i;
	int	start;

	i = 0;
	start = -1;
	while (string[i])
	{
		if (!is_space(string[i]))
		{
			start = i;
			break ;
		}
		i++;
	}
	return (start);
}

int	get_end(int start, char *string)
{
	int	i;

	i = start;
	while (string[i] && !is_space(string[i]))
	{
		i++;
	}
	return (i - 1);
}

int	main(int ac, char **av)
{
	char	*string;
	int		start;
	int		end;

	if (ac != 2)
	{
		write(1, "\n", 1);
		return (0);
	}
	string = av[1];
	start = get_start(string);
	if (start < 0)
	{
		write(1, "\n", 1);
		return (0);
	}
	end = get_end(start, string);
	while (start <= end)
	{
		write(1, &string[start], 1);
		start++;
	}
	write(1, "\n", 1);
	return (0);
}

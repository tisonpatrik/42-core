

#include <unistd.h>

int	get_alpha_index(char c)
{
	if (c >= 'a' && c <= 'z')
		return (c - 'a' + 1);
	if (c >= 'A' && c <= 'Z')
		return (c - 'A' + 1);
	return (-1);
}
int	main(int ac, char **av)
{
	char	*string;
	int		i;
	int		index;
	int		j;

	string = av[1];
	i = 0;
	while (string[i])
	{
		index = get_alpha_index(string[i]);
		if (index > 0)
		{
			j = 0;
			while (j < index)
			{
				write(1, &string[i], 1);
				j++;
			}
		}
		else
		{
			write(1, &string[i], 1);
		}
		i++;
	}
	write(1, "\n", 1);
	return (0);
}



#include <stdio.h>

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

char	*ft_strrev(char *str)
{
	int		len;
	char	tmp;
	int		i;

	len = get_len(str) -1;
	i = 0;
	while (i < len)
	{
		tmp = str[i];
		str[i] = str[len];
		str[len] = tmp;
		i++;
		len--;
	}
	return (str);
}

int	main(int ac, char **av)
{
	char	*string;
	char	*current;

	string = av[1];
	current = ft_strrev(string);
	printf("current: %s\n", current);
}

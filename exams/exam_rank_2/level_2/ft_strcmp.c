#include <stdio.h>
#include <string.h>

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] != '\0' && s2[i] != '\0' && s1[i] == s2[i])
		i++;
	return (s1[i] - s2[i]);
}

int	main(int ac, char **av)
{
	int	result;

	result = ft_strcmp(av[1], av[2]);
	printf("%d\n", strcmp(av[1], av[2]));
	printf("%d\n", result);
	return (0);
}

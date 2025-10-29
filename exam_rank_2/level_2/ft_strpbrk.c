
#include <stdio.h>
#include <string.h>

char	*ft_strpbrk(const char *s1, const char *s2)
{
	int	i;
	int	j;

	i = 0;
	while (s1[i])
	{
		j = 0;
		while (s2[j])
		{
			if (s1[i] == s2[j])
			{
				return ((char *)&s1[i]);
			}
			j++;
		}
		i++;
	}
	return (NULL);
}

int	main(int ac, char **av)
{
	char	*result;

	result = ft_strpbrk(av[1], av[2]);
	printf("%s\n", strpbrk(av[1], av[2]));
	printf("%s\n", result);
	return (0);
}

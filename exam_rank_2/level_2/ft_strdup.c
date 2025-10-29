
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int	get_len(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

char	*ft_strdup(char *src)
{
	int		len;
	char	*dup;
	int		i;

	len = get_len(src);
	dup = malloc(sizeof(char) * len + 1);
	if (dup == NULL)
		return (NULL);
	i = 0;
	while (src[i])
	{
		dup[i] = src[i];
		i++;
	}
	dup[i] = '\0';
	return (dup);
}

int	main(int ac, char **av)
{
	printf("%s\n", strdup(av[1]));
	printf("%s\n", ft_strdup(av[1]));
}

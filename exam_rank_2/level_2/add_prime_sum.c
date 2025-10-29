#include <stdbool.h>

bool	is_prime(int nbr)
{
	int	i;
	int	count;

	if (nbr <= 1)
		return (false);
	i = 0;
	count = 0;
	while (i <= nbr)
	{
		if (nbr % i == 0)
			count++;
		i++;
	}
	if (count > 2)
		return (false);
	else
		return (true);
}
int	main(int ac, char **av)
{
	return (0);
}

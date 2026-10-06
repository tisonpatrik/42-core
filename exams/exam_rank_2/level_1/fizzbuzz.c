
#include <unistd.h>

void	put_number(int n)
{
	char	*decimal;

	decimal = "0123456789";
	if (n >= 10)
		put_number(n / 10);
	write(1, &decimal[n % 10], 1);
}

int	main(int ac, char **av)
{
	int	i;
	int	mod_3;
	int	mod_5;

	i = 1;
	while (i <= 100)
	{
		mod_3 = i % 3;
		mod_5 = i % 5;
		if ((mod_3 == 0) && (mod_5 == 0))
		{
			write(1, "fizzbuzz", 8);
		}
		else if (mod_3 == 0)
		{
			write(1, "fizz", 4);
		}
		else if (mod_5 == 0)
		{
			write(1, "buzz", 4);
		}
		else
		{
			put_number(i);
		}
		write(1, "\n", 1);
		i++;
	}
}

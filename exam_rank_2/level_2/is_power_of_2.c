

#include <stdio.h>
#include <stdlib.h>

int	is_power_of_2(unsigned int n)
{
	return (n > 0) && ((n & (n - 1)) == 0);
}
// 0000 0111 & 0000 0110 -> 1
int	main(int ac, char **av)
{
	int	number;
	int	is_power;

	number = atoi(av[1]);
	is_power = is_power_of_2(number);
	printf("%d\n", is_power);
	return (0);
}

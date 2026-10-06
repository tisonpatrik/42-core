#include <stdio.h>

void	ft_swap(int *a, int *b)
{
	int	tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
}

int	main(int ac, char **av)
{
	int	a;
	int	b;

	a = 5;
	b = 10;
	ft_swap(&a, &b);
	printf("a: %d \nb: %d \n", a, b);
}

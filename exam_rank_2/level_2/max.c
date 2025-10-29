
#include <stdio.h>
int	max(int *tab, unsigned int len)
{
	int	i;
	int	max;

	if (len == 0)
		return (0);
	i = 1;
	max = tab[0];
	while (i < len)
	{
		if (tab[i] > max)
			max = tab[i];
		i++;
	}
	return (max);
}


int main()
{
    int tab1[] = {10, -5, 42, 33, 9, 78, 1};
    unsigned int len1 = 7;
    int result = max(tab1, len1);
	
	printf("%d\n", result);
    return 0;
}

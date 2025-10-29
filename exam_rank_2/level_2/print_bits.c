
#include <unistd.h>

void	print_bits(unsigned char octet)
{
	int				i;
	unsigned char	bit_mask;
	char			bit_char;

	i = 7;
	bit_mask = 1 << 7;
	while (i >= 0)
	{
		if (octet & bit_mask)
		{
			bit_char = '1';
		}
		else
		{
			bit_char = '0';
		}
		write(1, &bit_char, 1);
		bit_mask = bit_mask >> 1;
		i--;
	}
}
int	main(int ac, char **av)
{
	unsigned char	c;

	c = '2';
	print_bits(c);
	return (0);
}

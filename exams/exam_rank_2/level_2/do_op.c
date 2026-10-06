#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

typedef struct s_result
{
	bool	success;
	int		value;
}			t_result;

int	get_len(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

t_result	perform_operation(int a, char *str, int b)
{
	int			len;
	t_result	result;

	result.success = true;
	result.value = 0.0;
	len = get_len(str);
	if (len != 1)
	{
		result.success = false;
		return (result);
	}
	char operator= str[0];
	if (operator== '+')
	{
		result.value = a + b;
		return (result);
	}
	else if (operator== '-')
	{
		result.value = a - b;
		return (result);
	}
	else if (operator== '*')
	{
		result.value = a * b;
		return (result);
	}
	else if (operator== '/')
	{
		if (b != 0)
		{
			result.value = a / b;
			return (result);
		}
		else
		{
			result.success = false;
			return (result);
		}
	}
	else if (operator== '%')
	{
		result.value = a % b;
		return (result);
	}
	else
	{
		result.success = false;
		return (result);
	}
}

int	main(int ac, char **av)
{
	int			x1;
	int			x2;
	t_result	result;

	if (ac != 4)
	{
		write(1, "\n", 1);
		return (0);
	}
	x1 = atoi(av[1]);
	x2 = atoi(av[3]);
	result = perform_operation(x1, av[2], x2);
	if (result.success == true)
	{
		printf("%d\n", result.value);
	}
	else
	{
		printf("Error\n");
	}
	return (0);
}

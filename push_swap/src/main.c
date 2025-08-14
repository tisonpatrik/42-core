#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <libft.h>


int	exit_with_error(void)
{
	fprintf(stderr, "Error\n");
	return (-1);
}

int	ft_check(t_list *lst, int n, char *nbr)
{
	t_list	*tmp;
	int		i;

	tmp = lst;
	i = 0;
	while (nbr[i])
	{
		if (!(((nbr[i] == '-' || nbr[i] == '+') && ft_isdigit(nbr[i + 1])
					&& (i == 0 || !ft_isdigit(nbr[i - 1])))
				|| ft_isdigit(nbr[i])))
			return (0);
		i++;
	}
	while (tmp)
	{
		if (tmp->content == n)
			return (0);
		tmp = tmp->next;
	}
	return (1);
}

t_list	*ft_init(char **ag, int ac)
{
	t_list	*tmp;
	t_list	*res;
	int		i;
	long	nbr;

	if (ac == 2)
		i = 0;
	else
		i = 1;
	res = NULL;
	while (ag[i])
	{
		nbr = ft_atoi(ag[i]);
		if (nbr > INT_MAX || nbr < INT_MIN || ft_check(res, nbr, ag[i]) == 0)
		{
			ft_putstr_fd("Error\n", 2);
			return (NULL);
		}
		tmp = ft_lstnew(nbr);
		ft_lstadd_back(&res, tmp);
		tmp->index = -1;
		i++;
	}
	return (res);
}


int	main(int ac, char **av)
{
	int	count;
	int	*inputs;

	if (ac < 2)
	{
		return (exit_with_error());
	}
	count = ac - 1;
	inputs = malloc(count * sizeof(int));
	if (inputs == NULL)
	{
		return (exit_with_error());
	}
	if (validate_inputs(count, av, inputs) != 0)
	{
		return (exit_with_error());
	}
	for (int i = 0; i < count; i++)
	{
		printf("%d ", inputs[i]);
	}
	printf("\n");
	free(inputs);
	return (0);
}

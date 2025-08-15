/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: patrik <patrik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 20:16:34 by ptison            #+#    #+#             */
/*   Updated: 2025/08/15 16:08:05 by patrik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/push_swap.h"
#include "../libft/libft.h"
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

int	exit_with_error(void)
{
	fprintf(stderr, "Error\n");
	return (-1);
}
int	ft_check(t_list *lst, int n, const char *nbr)
{
	int	i;
	long long check;

	i = 0;
	if (nbr[i] == '+' || nbr[i] == '-')
		i++;
	if (!nbr[i])
		return (0);
	for (; nbr[i]; i++)
		if (!ft_isdigit((unsigned char)nbr[i]))
			return (0);
	
	// Kontrola overflow - pokud atoi vrací 0 ale string není "0"
	check = ft_atoi(nbr);
	if (check == 0 && (nbr[0] != '0' || (nbr[0] == '-' && nbr[1] != '0') || (nbr[0] == '+' && nbr[1] != '0')))
		return (0);
	
	for (t_list *tmp = lst; tmp; tmp = tmp->next)
		if (*(int *)tmp->content == n)
			return (0);
	return (1);
}
t_list	*ft_init(char **ag)
{
	t_list	*res;
	t_list	*tmp;
	int		i;
	long	nbr;
	int		*val;

	res = NULL;
	i = 1;
	while (ag[i])
	{
		nbr = ft_atoi(ag[i]);
		// Kontrola overflow - pokud atoi vrací 0 ale string není "0"
		if (nbr == 0 && (ag[i][0] != '0' || (ag[i][0] == '-' && ag[i][1] != '0') || (ag[i][0] == '+' && ag[i][1] != '0')))
		{
			ft_lstclear(&res, free);
			return (NULL);
		}
		if (nbr > INT_MAX || nbr < INT_MIN || ft_check(res, (int)nbr, ag[i]) == 0)
		{
			ft_lstclear(&res, free);
			return (NULL);
		}
		val = malloc(sizeof *val);
		if (!val)
		{
			ft_lstclear(&res, free);
			return (NULL);
		}
		*val = (int)nbr;
		tmp = ft_lstnew(val);
		if (!tmp)
		{
			free(val);
			ft_lstclear(&res, free);
			return (NULL);
		}
		ft_lstadd_back(&res, tmp);
		i++;
	}
	return (res);
}

int	main(int ac, char **args)
{
	t_swap	*tab;

	tab = NULL;
	if (ac < 2)
		return (exit_with_error());
	tab = malloc(sizeof *tab);
	if (!tab)
		return (exit_with_error());
	tab->stack_a = ft_init(args);
	if (!tab->stack_a)
	{
		free(tab);
		return (exit_with_error());
	}
	for (t_list *tmp = tab->stack_a; tmp; tmp = tmp->next)
		printf("%d ", *(int *)tmp->content);
	printf("\n");
	ft_lstclear(&tab->stack_a, free);
	free(tab);
	return (0);
}

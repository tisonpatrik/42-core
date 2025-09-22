/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reader_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptison <ptison@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 18:27:42 by ptison            #+#    #+#             */
/*   Updated: 2025/09/22 18:27:43 by ptison           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../include/ops.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

t_operation	parse_operation_string(const char *str)
{
	if (ft_strncmp(str, "sa", 2) == 0)
		return (SA);
	else if (ft_strncmp(str, "sb", 2) == 0)
		return (SB);
	else if (ft_strncmp(str, "ss", 2) == 0)
		return (SS);
	else if (ft_strncmp(str, "pa", 2) == 0)
		return (PA);
	else if (ft_strncmp(str, "pb", 2) == 0)
		return (PB);
	else if (ft_strncmp(str, "ra", 2) == 0)
		return (RA);
	else if (ft_strncmp(str, "rb", 2) == 0)
		return (RB);
	else if (ft_strncmp(str, "rr", 2) == 0)
		return (RR);
	else if (ft_strncmp(str, "rra", 3) == 0)
		return (RRA);
	else if (ft_strncmp(str, "rrb", 3) == 0)
		return (RRB);
	else if (ft_strncmp(str, "rrr", 3) == 0)
		return (RRR);
	else
		return (-1);
}


t_list	*get_operations(void)
{
	t_list		*operations;
	t_list		*new_node;
	t_operation	op;
	char		*line;
	char		*trimmed;

	operations = NULL;
	while (1)
	{
		line = get_next_line(STDIN_FILENO);
		if (!line)
			break ;
		trimmed = ft_strtrim(line, "\n\r");
		free(line);
		if (!trimmed)
			continue ;
		op = parse_operation_string(trimmed);
		free(trimmed);
		if (op == -1)
		{
			ft_lstclear(&operations, free);
			return (NULL);
		}
		new_node = ft_lstnew(&op);
		if (!new_node)
		{
			ft_lstclear(&operations, free);
			return (NULL);
		}
		ft_lstadd_back(&operations, new_node);
	}
	return (operations);
}

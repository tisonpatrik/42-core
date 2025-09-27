/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reader_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptison <ptison@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 18:27:42 by ptison            #+#    #+#             */
/*   Updated: 2025/09/27 11:37:30 by ptison           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ops.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

static t_operation	parse_operation_string(const char *str)
{
	if (ft_strncmp(str, "sa", 3) == 0 && ft_strlen(str) == 2)
		return (SA);
	else if (ft_strncmp(str, "sb", 3) == 0 && ft_strlen(str) == 2)
		return (SB);
	else if (ft_strncmp(str, "ss", 3) == 0 && ft_strlen(str) == 2)
		return (SS);
	else if (ft_strncmp(str, "pa", 3) == 0 && ft_strlen(str) == 2)
		return (PA);
	else if (ft_strncmp(str, "pb", 3) == 0 && ft_strlen(str) == 2)
		return (PB);
	else if (ft_strncmp(str, "ra", 3) == 0 && ft_strlen(str) == 2)
		return (RA);
	else if (ft_strncmp(str, "rb", 3) == 0 && ft_strlen(str) == 2)
		return (RB);
	else if (ft_strncmp(str, "rra", 4) == 0 && ft_strlen(str) == 3)
		return (RRA);
	else if (ft_strncmp(str, "rrb", 4) == 0 && ft_strlen(str) == 3)
		return (RRB);
	else if (ft_strncmp(str, "rrr", 4) == 0 && ft_strlen(str) == 3)
		return (RRR);
	else if (ft_strncmp(str, "rr", 3) == 0 && ft_strlen(str) == 2)
		return (RR);
	return (OP_INVALID);
}

static t_operation	process_operation_line(void)
{
	char		*line;
	char		*trimmed_line;
	t_operation	op;

	line = ft_get_line(STDIN_FILENO);
	if (line == NULL)
		return (OP_EOF);
	trimmed_line = ft_strtrim(line, "\n");
	free(line);
	if (trimmed_line == NULL)
		return (OP_ALLOC_FAIL);
	op = parse_operation_string(trimmed_line);
	free(trimmed_line);
	return (op);
}

static t_list	*create_operation_node(t_operation op)
{
	t_operation	*op_ptr;
	t_list		*new_node;

	op_ptr = malloc(sizeof(t_operation));
	if (!op_ptr)
		return (NULL);
	*op_ptr = op;
	new_node = ft_lstnew(op_ptr);
	if (!new_node)
	{
		free(op_ptr);
		return (NULL);
	}
	return (new_node);
}

static int	add_operation_to_list(t_list **operations, t_operation op)
{
	t_list	*new_node;

	if (op == OP_INVALID)
	{
		ft_lstclear(operations, free);
		return (0);
	}
	new_node = create_operation_node(op);
	if (!new_node)
	{
		ft_lstclear(operations, free);
		return (0);
	}
	ft_lstadd_back(operations, new_node);
	return (1);
}

t_list	*get_operations(void)
{
	t_list		*operations;
	t_operation	op;

	operations = NULL;
	while (1)
	{
		op = process_operation_line();
		if (op == OP_EOF)
			break ;
		if (op == OP_ALLOC_FAIL)
			continue ;
		if (!add_operation_to_list(&operations, op))
			return (NULL);
	}
	return (operations);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reader_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptison <ptison@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 18:27:42 by ptison            #+#    #+#             */
/*   Updated: 2025/09/23 18:58:39 by ptison           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../include/ops.h"
#include "../../libft/include/libft.h"
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
	else
		return (OP_INVALID);
}

static t_operation	process_operation_line(void)
{
	char		*line;
	t_operation	op;
	size_t		len;
	ssize_t		bytes_read;

	line = NULL;
	len = 0;
	bytes_read = getline(&line, &len, stdin);
	if (bytes_read <= 0)
	{
		if (line)
			free(line);
		return (OP_EOF);
	}
	// Remove newline
	if (bytes_read > 0 && line[bytes_read - 1] == '\n')
		line[bytes_read - 1] = '\0';
	op = parse_operation_string(line);
	free(line);
	return (op);
}


t_list	*get_operations(void)
{
	t_list		*operations;
	t_list		*new_node;
	t_operation	op;

	operations = NULL;
	while (1)
	{
		op = process_operation_line();
		if (op == OP_EOF)
			break ;
		if (op == OP_ALLOC_FAIL)
			continue ;
		if (op == OP_INVALID)
		{
			ft_lstclear(&operations, free);
			return (NULL);
		}
		t_operation *op_ptr = malloc(sizeof(t_operation));
		if (!op_ptr)
		{
			ft_lstclear(&operations, free);
			return (NULL);
		}
		*op_ptr = op;
		new_node = ft_lstnew(op_ptr);
		if (!new_node)
		{
			free(op_ptr);
			ft_lstclear(&operations, free);
			return (NULL);
		}
		ft_lstadd_back(&operations, new_node);
	}
	return (operations);
}

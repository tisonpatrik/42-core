/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   separator.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: patrik <patrik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 19:24:28 by patrik            #+#    #+#             */
/*   Updated: 2025/09/09 19:31:25 by patrik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SEPARATOR_H
# define SEPARATOR_H

#include <stdbool.h>
#include "stack.h"
#include <stddef.h>
#include "ops.h"

typedef struct s_tnode_bool {
    t_node* node;
    bool    value;
} t_node_bool;

typedef struct s_node_bool_array {
    t_node_bool* items;
    size_t       count;
} t_node_bool_array;

typedef struct s_lis_result
{
	int	best_len;
	int	best_end;
}	t_lis_result;

typedef struct s_lis_computation_data
{
	int	*vals;
	int	n;
	int	*lis;
	int	*prev;
}	t_lis_computation_data;

typedef struct s_allocation_data
{
	int				n;
	t_node			***nodes;
	int				**vals;
	int				**lis;
	int				**prev;
}	t_allocation_data;

t_node_bool_array* get_lis_nodes(t_stack *stack);
t_node_bool_array* get_lis_nodes_impl(t_stack *stack, int n);
void push_non_lis_into_b(t_sorting_state *state);

#endif

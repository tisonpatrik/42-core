/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: patrik <patrik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 19:24:41 by patrik            #+#    #+#             */
/*   Updated: 2025/09/11 21:50:13 by patrik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STACK_H
# define STACK_H

# include <stdbool.h>

typedef struct s_node
{
	int				content;
	struct s_node	*next;
	struct s_node	*prev;
}	t_node;

typedef struct s_stack
{
	t_node			*head;
	t_node			*tail;
	int				size;
}	t_stack;

// Stack operations
t_stack			*create_stack(void);
int				get_size(t_stack *stack);
void			push_to_stack(t_stack *stack, t_node *node);
t_node			*pop(t_stack **stack);
t_node			*create_node(int content);
void			clear_stack(t_stack *stack);
void			fill_stack(t_stack *stack, int *numbers, int n);
bool			is_sorted(t_stack *stack);
t_node			*get_head(t_stack *stack);
t_node			*get_tail(t_stack *stack);
int				get_content(t_node *node);
t_node			*get_next(t_node *node);
t_node			*get_prev(t_node *node);

// Simulation helper functions
t_stack			*clone_stack(t_stack *original);
void			free_stack(t_stack *stack);
t_node			*get_node_at_index(t_stack *stack, int index);
void			remove_node_from_stack(t_stack *stack, t_node *node);
void			insert_node_at_index(t_stack *stack, t_node *node, int index);
void			print_stack_values(t_stack *stack);

#endif
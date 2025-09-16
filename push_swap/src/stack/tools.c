/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: patrik <patrik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 18:48:36 by ptison            #+#    #+#             */
/*   Updated: 2025/09/16 21:40:58 by patrik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/stack.h"
#include "../../libft/include/libft.h"
#include <stdbool.h>
#include <stdlib.h>

void	clear_stack(t_stack *stack)
{
	t_node	*current;
	t_node	*next;

	if (!stack)
		return ;
	current = get_head(stack);
	while (current)
	{
		next = get_next(current);
		free(current);
		current = next;
	}
	stack->head = NULL;
	stack->tail = NULL;
	stack->size = 0;
}

void	fill_stack(t_stack *stack, int *numbers, int n)
{
	t_node	*node;
	int		i;

	clear_stack(stack);
	i = n - 1;
	while (i >= 0)
	{
		node = create_node(numbers[i]);
		push_to_stack(stack, node);
		i--;
	}
}

bool	is_sorted(t_stack *stack)
{
	t_node	*current;
	t_node	*next;

	if (!stack || get_size(stack) <= 1)
		return (true);
	current = get_head(stack);
	next = get_next(current);
	while (next != NULL)
	{
		if (get_content(current) > get_content(next))
			return (false);
		current = next;
		next = get_next(current);
	}
	return (true);
}

t_stack	*clone_stack(t_stack *original)
{
	t_stack	*clone;
	t_node	*current;
	t_node	*new_node;

	if (!original)
		return (NULL);
	clone = create_stack();
	if (!clone)
		return (NULL);
	current = get_head(original);
	while (current)
	{
		new_node = create_node(get_content(current));
		if (!new_node)
		{
			clear_stack(clone);
			free(clone);
			return (NULL);
		}
		push_to_stack(clone, new_node);
		current = get_next(current);
	}
	return (clone);
}

void	free_stack(t_stack *stack)
{
	if (!stack)
		return ;
	clear_stack(stack);
	free(stack);
}

t_node	*get_node_at_index(t_stack *stack, int index)
{
	t_node	*current;
	int		i;

	if (!stack || index < 0 || index >= get_size(stack))
		return (NULL);
	current = get_head(stack);
	i = 0;
	while (i < index)
	{
		current = get_next(current);
		i++;
	}
	return (current);
}

void	remove_node_from_stack(t_stack *stack, t_node *node)
{
	if (!stack || !node)
		return ;
	if (node->prev)
		node->prev->next = node->next;
	else
		stack->head = node->next;
	if (node->next)
		node->next->prev = node->prev;
	else
		stack->tail = node->prev;
	stack->size--;
	node->next = NULL;
	node->prev = NULL;
}

void	insert_node_at_index(t_stack *stack, t_node *node, int index)
{
	t_node	*target_node;

	if (!stack || !node || index < 0 || index > get_size(stack))
		return ;
	if (index == 0)
	{
		push_to_stack(stack, node);
		return ;
	}
	if (index == get_size(stack))
	{
		if (stack->tail)
		{
			stack->tail->next = node;
			node->prev = stack->tail;
			node->next = NULL;
			stack->tail = node;
		}
		else
		{
			stack->head = node;
			stack->tail = node;
			node->next = NULL;
			node->prev = NULL;
		}
		stack->size++;
		return ;
	}
	target_node = get_node_at_index(stack, index);
	if (!target_node)
		return ;
	node->next = target_node;
	node->prev = target_node->prev;
	if (target_node->prev)
		target_node->prev->next = node;
	else
		stack->head = node;
	target_node->prev = node;
	stack->size++;
}

void	print_stack_values(t_stack *stack)
{
	t_node	*current;

	if (!stack)
	{
		ft_putstr_fd("(empty)", 1);
		return ;
	}
	current = get_head(stack);
	while (current)
	{
		ft_putnbr_fd(get_content(current), 1);
		current = get_next(current);
		if (current)
			ft_putstr_fd(" ", 1);
	}
}

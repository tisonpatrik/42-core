
#include "../../include/optimizer.h"

t_operation	get_operation_at_index(t_list *list, int index)
{
	t_list	*current = list;
	int		i = 0;
	
	while (current != NULL && i < index)
	{
		current = current->next;
		i++;
	}
	
	if (current == NULL)
		return (SA);
	return (*(t_operation*)current->content);
}

void	set_operation_at_index(t_list *list, int index, t_operation op)
{
	t_list	*current = list;
	int		i = 0;
	
	while (current != NULL && i < index)
	{
		current = current->next;
		i++;
	}
	
	if (current != NULL)
		*(t_operation*)current->content = op;
}

bool	bubble_operation(t_list *out, int i, int j, bool is_a)
{
	for (int k = i + 1; k < j; k++)
	{
		t_operation op_k = get_operation_at_index(out, k);
		if (is_barrier(op_k))
			return (false);
		if (is_a && (touches_a(op_k) || (!touches_b(op_k) && !is_pure_b(op_k))))
			return (false);
		if (!is_a && (touches_b(op_k) || (!touches_a(op_k) && !is_pure_a(op_k))))
			return (false);
	}
	for (int k = j; k > i + 1; k--)
	{
		t_operation temp = get_operation_at_index(out, k);
		set_operation_at_index(out, k, get_operation_at_index(out, k - 1));
		set_operation_at_index(out, k - 1, temp);
	}
	return (true);
}

t_list	*bubble_across_other_stack(t_list *src, int max_gap, bool *changed)
{
	int		n = ft_lstsize(src);
	t_list	*out;
	int		i;

	if (n < 3)
	{
		*changed = false;
		return (src);
	}
	out = ft_lstmap(src, copy_operation, free);
	if (out == NULL)
		return (NULL);
	*changed = false;
	i = 0;
	while (i < n - 1)
	{
		process_operation_at_index(out, i, n, max_gap, changed);
		i++;
	}
	return (out);
}

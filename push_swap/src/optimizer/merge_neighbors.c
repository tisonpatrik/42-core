
#include "../../include/optimizer.h"

t_list	*merge_neighbors(t_list *src, bool *changed)
{
	if (!src || ft_lstsize(src) < 2)
	{
		if (changed)
			*changed = false;
		return (ft_lstmap(src, copy_operation, free));
	}
	
	t_list	*dst = NULL;
	bool	has_changed = false;
	t_list	*current = src;
	
	while (current != NULL)
	{
		if (current->next != NULL)
		{
			t_operation a = *(t_operation*)current->content;
			t_operation b = *(t_operation*)current->next->content;
			
			if (try_merge_operations(a, b, &dst, &current))
			{
				has_changed = true;
				continue;
			}
		}
		add_operation_to_list(&dst, *(t_operation*)current->content);
		current = current->next;
	}
	
	if (changed)
		*changed = has_changed;
	
	return (dst);
}

#ifndef OPTIMIZER_H
# define OPTIMIZER_H

# include "../libft/include/libft.h"
# include "ops.h"
# include <stdlib.h>

// Main optimization function
t_list	*optimize_ops(t_list *seq);

// Bubble operations
t_list	*bubble_across_other_stack(t_list *src, int max_gap);
bool	is_pure_a(t_operation op);
bool	is_pure_b(t_operation op);

// Merge neighbors
t_list	*merge_neighbors(t_list *src);

// Cancel operations
t_list	*cancel_inverse_pairs(t_list *src);
bool	is_inverse(t_operation a, t_operation b);
t_list	*cancel_across_other_stack_a(t_list *src);
t_list	*cancel_across_other_stack_b(t_list *src);

// Operation properties
bool	touches_a(t_operation op);
bool	touches_b(t_operation op);
bool	is_barrier(t_operation op);

// Helper functions for list operations
t_list	*list_copy(t_list *src);
void	list_swap_nodes(t_list *list, int i, int j);
t_list	*list_remove_at(t_list *list, int index);
t_list	*list_insert_at(t_list *list, t_operation op, int index);
t_operation	get_operation_at_index(t_list *list, int index);
void	set_operation_at_index(t_list *list, int index, t_operation op);
bool	bubble_operation(t_list *out, int i, int j, bool is_a);

#endif

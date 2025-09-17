#include "../../include/ops.h"

void	print_operation(t_operation op)
{
	if (op == SA)
		ft_printf("sa\n");
	else if (op == SB)
		ft_printf("sb\n");
	else if (op == SS)
		ft_printf("ss\n");
	else if (op == PA)
		ft_printf("pa\n");
	else if (op == PB)
		ft_printf("pb\n");
	else if (op == RA)
		ft_printf("ra\n");
	else if (op == RB)
		ft_printf("rb\n");
	else if (op == RR)
		ft_printf("rr\n");
	else if (op == RRA)
		ft_printf("rra\n");
	else if (op == RRB)
		ft_printf("rrb\n");
	else if (op == RRR)
		ft_printf("rrr\n");
}

void	print_operations(t_sorting_state *state)
{
	t_list		*current;
	t_operation	op;

	current = state->operations;
	while (current != NULL)
	{
		op = *(t_operation *)current->content;
		print_operation(op);
		current = current->next;
	}
}

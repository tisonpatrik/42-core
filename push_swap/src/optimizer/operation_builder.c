
#include "../../include/optimizer.h"

t_operation_builder	*create_operation_builder(t_optimizer_arena *arena)
{
	t_operation_builder	*builder;

	if (!arena)
		return (NULL);
	builder = malloc(sizeof(t_operation_builder));
	if (!builder)
		return (NULL);
	builder->arena = arena;
	builder->result = NULL;
	builder->changed = false;
	builder->error = OPTIMIZER_SUCCESS;
	return (builder);
}

void	destroy_operation_builder(t_operation_builder *builder)
{
	if (!builder)
		return;
	if (builder->result)
		ft_lstclear(&builder->result, free);
	free(builder);
}

t_optimizer_error	add_operation_to_builder(t_operation_builder *builder, t_operation op)
{
	t_operation	*op_ptr;

	if (!builder)
		return (OPTIMIZER_INVALID_INPUT);
	op_ptr = malloc(sizeof(t_operation));
	if (!op_ptr)
	{
		builder->error = OPTIMIZER_MEMORY_ERROR;
		return (OPTIMIZER_MEMORY_ERROR);
	}
	*op_ptr = op;
	ft_lstadd_back(&builder->result, ft_lstnew(op_ptr));
	return (OPTIMIZER_SUCCESS);
}

t_optimizer_error	copy_operations_to_builder(t_operation_builder *builder, 
												t_list *src_start, t_list *src_end)
{
	t_list	*current;

	if (!builder || !src_start)
		return (OPTIMIZER_INVALID_INPUT);
	current = src_start;
	while (current != src_end)
	{
		if (add_operation_to_builder(builder, *(t_operation*)current->content) != OPTIMIZER_SUCCESS)
			return (builder->error);
		current = current->next;
	}
	return (OPTIMIZER_SUCCESS);
}

t_list	*builder_get_result(t_operation_builder *builder)
{
	if (!builder)
		return (NULL);
	return (builder->result);
}

bool	builder_has_changed(t_operation_builder *builder)
{
	if (!builder)
		return (false);
	return (builder->changed);
}

void	builder_mark_changed(t_operation_builder *builder)
{
	if (builder)
		builder->changed = true;
}

t_optimizer_error	builder_get_error(t_operation_builder *builder)
{
	if (!builder)
		return (OPTIMIZER_INVALID_INPUT);
	return (builder->error);
}

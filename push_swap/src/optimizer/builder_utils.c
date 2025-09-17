#include "../../include/optimizer.h"

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

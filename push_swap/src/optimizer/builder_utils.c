/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builder_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptison <ptison@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/19 20:50:16 by ptison            #+#    #+#             */
/*   Updated: 2025/09/19 20:50:18 by ptison           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

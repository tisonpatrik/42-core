/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_skip_whitespace.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptison <ptison@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 18:54:17 by ptison            #+#    #+#             */
/*   Updated: 2025/08/19 18:54:19 by ptison           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/core.h"

void	ft_skip_whitespace(const char **current_position)
{
	while (ft_isspace((unsigned char)**current_position))
		(*current_position)++;
}


#include "../../include/ft/core.h"

void	ft_skip_whitespace(const char **current_position)
{
	while (ft_isspace((unsigned char)**current_position))
		(*current_position)++;
}
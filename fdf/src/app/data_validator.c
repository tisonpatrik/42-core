/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_validator.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptison <ptison@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 23:25:35 by ptison            #+#    #+#             */
/*   Updated: 2025/10/13 23:25:37 by ptison           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../include/old_app.h"

/* ========================================================================== */
/* DATA VALIDATION FUNCTIONS - Pure validation logic                         */
/* ========================================================================== */

int	hex_to_int(const char *hex_str)
{
	int	result;
	int	i;

	result = 0;
	i = 0;
	while (hex_str[i])
	{
		result *= 16;
		if (hex_str[i] >= '0' && hex_str[i] <= '9')
			result += hex_str[i] - '0';
		else if (hex_str[i] >= 'A' && hex_str[i] <= 'F')
			result += hex_str[i] - 'A' + 10;
		else if (hex_str[i] >= 'a' && hex_str[i] <= 'f')
			result += hex_str[i] - 'a' + 10;
		i++;
	}
	return (result);
}

int	parse_color_from_token(char *token)
{
	while (*token == '-')
		token++;
	while (ft_isdigit(*token))
		token++;
	if (*token == ',')
		token++;
	else
		return (0xFFFFFFFF);
	if ((ft_strncmp(token, "0X", 2) && ft_strncmp(token, "0x", 2)))
		return (-1); /* Invalid color format */
	token += 2;
	ft_striteri(token, &make_upper);
	return ((hex_to_int(token) << 8) | 0xFF);
}

int	validate_map_line(char *line)
{
	char	**tokens;
	int		i;
	int		valid;

	tokens = ft_split(line, ' ');
	if (!tokens)
		return (0);
	
	valid = 1;
	i = 0;
	while (tokens[i])
	{
		if (!ft_isdigit(*tokens[i]) && *tokens[i] != '-')
		{
			valid = 0;
			break;
		}
		i++;
	}
	
	ft_free_tab((void **)tokens, i);
	return (valid);
}

int	get_column_count(char *line)
{
	char	**tokens;
	int		count;

	tokens = ft_split(line, ' ');
	if (!tokens)
		return (0);
	
	count = 0;
	while (tokens[count])
		count++;
	
	ft_free_tab((void **)tokens, count);
	return (count);
}

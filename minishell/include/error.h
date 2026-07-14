/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omaly <student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/26 12:31:40 by omaly             #+#    #+#             */
/*   Updated: 2026/02/26 12:31:45 by omaly            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_H
# define ERROR_H

# include "../libft/include/libft.h"
# include <stdio.h>
# include <unistd.h>

void	shell_error(const char *cmd, const char *arg, const char *msg);
void	shell_perror(const char *cmd, const char *arg);

#endif

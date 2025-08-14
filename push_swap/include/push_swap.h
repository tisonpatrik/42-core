/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptison <ptison@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 20:13:12 by ptison            #+#    #+#             */
/*   Updated: 2025/08/14 21:17:04 by ptison           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"

typedef struct s_push
{
	int		next;
	int		max;
	int		mid;
	int		flag;
}			t_push;

typedef struct s_swap
{
	t_list	*stack_a;
	t_list	*stack_b;
	int		asize;
	int		bsize;
}			t_swap;

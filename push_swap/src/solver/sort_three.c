/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_three.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: patrik <patrik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 00:00:00 by patrik            #+#    #+#             */
/*   Updated: 2025/09/11 15:00:01 by patrik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/ops.h"
#include "../../include/stack.h"

// SortThree sorts a stack with exactly 3 elements using the optimal sequence of operations.
// It handles all 6 possible permutations of 3 elements with minimal operations.
void	sort_three(t_sorting_state *ps)
{
	if (get_size(ps->a) != 3)
		return ;

	t_node	*a = get_head(ps->a);
	t_node	*b = get_next(a);
	t_node	*c = get_next(b);

	int		x = get_content(a);
	int		y = get_content(b);
	int		z = get_content(c);

	// 5 cases (6 perms, 1 already sorted)
	if (x < y && y < z)
		return ; // sorted
	if (x > y && y < z && x < z)
	{
		swap_a(ps);
		return ; // 213
	}
	if (x > y && y > z)
	{
		swap_a(ps);
		reverse_rotate_a(ps);
		return ; // 321
	}
	if (x > y && y < z && x > z)
	{
		rotate_a(ps);
		return ; // 231
	}
	if (x < y && y > z && x < z)
	{
		swap_a(ps);
		rotate_a(ps);
		return ; // 132
	}
	// x < y && y > z && x > z
	reverse_rotate_a(ps); // 312
}

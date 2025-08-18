/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: patrik <patrik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 20:13:12 by ptison            #+#    #+#             */
/*   Updated: 2025/08/18 16:54:17 by patrik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/include/libft.h"


int				*indexize_array(const int *array, int len_of_array);

void			push_a(t_list **a, t_list **b);
void			push_b(t_list **a, t_list **b);
void			swap_a(t_list **a);
void			swap_b(t_list **b);
void			swap_ab(t_list **a, t_list **b);
void			rotate_a(t_list **a);
void			rotate_b(t_list **b);
void			rotate_ab(t_list **a, t_list **b);
void			reverse_rotate_a(t_list **a);
void			reverse_rotate_b(t_list **b);
void			reverse_rotate_aa(t_list **a, t_list **b);

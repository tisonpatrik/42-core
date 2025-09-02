/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: patrik <patrik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/17 10:21:27 by ptison            #+#    #+#             */
/*   Updated: 2025/09/02 12:44:13 by patrik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/ops.h"
#include <unistd.h>
#include <stdbool.h>

bool push(t_stack **source, t_stack **target)
{
    t_node *popped_node;
    
    if (!source || !*source)
        return false;
    if (!target || !*target)
        return false;
    if (get_size(*source) == 0)
        return false;
    
    popped_node = pop(source);
    if (!popped_node)
        return false;
    
    push_to_stack(*target, popped_node);
    return true;
}

// Take the first element at the top of b and put it at the top of a.
// Do nothing if b is empty.
void push_a(t_sorting_state *state)
{
    bool success = push(&state->b, &state->a);  // Push z B do A
    if (success)
        save_operation(state, PA);
}

// Take the first element at the top of a and put it at the top of b.
// Do nothing if a is empty.
void push_b(t_sorting_state *state)
{
    bool success = push(&state->a, &state->b);  // Push z A do B
    if (success)
        save_operation(state, PB);
}
#ifndef SEPARATOR_H
# define SEPARATOR_H

#include <stdbool.h>
#include "stack.h"
#include <stddef.h>
#include "ops.h"

typedef struct s_tnode_bool {
    t_node* node;
    bool    value;
} t_node_bool;

typedef struct s_node_bool_array {
    t_node_bool* items;
    size_t       count;
} t_node_bool_array;

t_node_bool_array* get_lis_nodes(t_stack *stack);
void push_non_lis_into_b(t_sorting_state *state);

#endif

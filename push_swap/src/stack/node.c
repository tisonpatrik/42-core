

#include <stdlib.h>
#include "../../include/stack.h"


t_node *create_node(int content)
{
    t_node *node = (t_node *)malloc(sizeof(t_node));
    if (!node)
        return NULL;
    node->content = content;
    node->next = NULL;
    node->prev = NULL;
    return node;
}
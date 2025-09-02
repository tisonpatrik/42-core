#include "../../include/stack.h"
#include <stdlib.h>

void push_to_stack(t_stack *stack, t_node *node)
{
    if (!stack || !node)
        return;
    
    node->next = stack->head;
    if (stack->head)
        stack->head->prev = node;
    else
        stack->tail = node;
    
    stack->head = node;
    stack->size++;
}

t_node *pop(t_stack **stack)
{
    t_node *popped_node;
    
    if (!stack || !*stack || (*stack)->size == 0)
        return NULL;
    
    popped_node = (*stack)->head;
    (*stack)->head = popped_node->next;
    
    if ((*stack)->head)
        (*stack)->head->prev = NULL;
    else
        (*stack)->tail = NULL;
    
    (*stack)->size--;
    popped_node->next = NULL;
    popped_node->prev = NULL;
    
    return popped_node;
}
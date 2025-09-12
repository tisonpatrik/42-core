#include "../include/separator.h"
#include "../include/stack.h"
#include <stdio.h>
#include <stdlib.h>
#include "test_main.h"

// Debug function to print LIS nodes
void test_lis_debug_function(void)
{
    printf("\n🔍 Debugging LIS Computation\n");
    printf("=============================\n");
    
    // Create test input: [3, 5, 2, 6, 1, 4, 0, 7, 9, 8, 10]
    int values[] = {3, 5, 2, 6, 1, 4, 0, 7, 9, 8, 10};
    int n = 11;
    
    // Create stack A with the test values
    t_stack *stack_a = create_stack();
    if (!stack_a) {
        printf("❌ Failed to create stack\n");
        return;
    }
    
    // Push values in reverse order (since we push to head)
    for (int i = n - 1; i >= 0; i--) {
        t_node *node = create_node(values[i]);
        if (!node) {
            printf("❌ Failed to create node for value %d\n", values[i]);
            free_stack(stack_a);
            return;
        }
        push_to_stack(stack_a, node);
    }
    
    printf("Input array: ");
    for (int i = 0; i < n; i++) {
        printf("%d ", values[i]);
    }
    printf("\n");
    
    // Get LIS nodes
    t_node_bool_array *lis_nodes = get_lis_nodes(stack_a);
    if (!lis_nodes) {
        printf("❌ Failed to compute LIS\n");
        free_stack(stack_a);
        return;
    }
    
    printf("LIS length: %zu\n", lis_nodes->count);
    printf("LIS nodes: ");
    for (size_t i = 0; i < lis_nodes->count; i++) {
        printf("%d ", get_content(lis_nodes->items[i].node));
    }
    printf("\n");
    
    // Show which elements are NOT in LIS
    printf("Non-LIS elements: ");
    t_node *current = get_head(stack_a);
    while (current) {
        bool in_lis = false;
        for (size_t i = 0; i < lis_nodes->count; i++) {
            if (lis_nodes->items[i].node == current) {
                in_lis = true;
                break;
            }
        }
        if (!in_lis) {
            printf("%d ", get_content(current));
        }
        current = get_next(current);
    }
    printf("\n");
    
    // Cleanup
    free(lis_nodes->items);
    free(lis_nodes);
    free_stack(stack_a);
}
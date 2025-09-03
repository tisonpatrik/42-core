#include "../../include/separator.h"
#include "../../include/stack.h"
#include <stdlib.h>
#include <stdbool.h>

void cleanup_tmp(t_node **nodes, int *vals, int *lis, int *prev) {
    free(nodes);
    free(vals);
    free(lis);
    free(prev);
}

t_node_bool_array* get_lis_nodes(t_stack *stack)
{
    int n = get_size(stack);
    if (n <= 0) {
        t_node_bool_array *empty = malloc(sizeof(*empty));
        if (!empty) return NULL;
        empty->items = NULL;
        empty->count = 0;
        return empty;
    }

    t_node **nodes = (t_node**)malloc(sizeof(t_node*) * (size_t)n);
    int    *vals   = (int*)malloc(sizeof(int) * (size_t)n);
    if (!nodes || !vals) { free(nodes); free(vals); return NULL; }

    t_node *cur = get_head(stack);
    for (int i = 0; i < n; ++i) {
        nodes[i] = cur;
        vals[i]  = get_content(cur);
        cur      = get_next(cur);
    }

    int *lis  = (int*)malloc(sizeof(int) * (size_t)n);
    int *prev = (int*)malloc(sizeof(int) * (size_t)n);
    if (!lis || !prev) { free(lis); free(prev); free(nodes); free(vals); return NULL; }

    int best_len = 0;
    int best_end = 0;

    for (int i = 0; i < n; ++i) {
        lis[i]  = 1;
        prev[i] = -1;
        for (int j = 0; j < i; ++j) {
            if (vals[j] < vals[i] && lis[j] + 1 > lis[i]) {
                lis[i]  = lis[j] + 1;
                prev[i] = j;
            }
        }
        if (lis[i] >= best_len) {
            best_len = lis[i];
            best_end = i;
        }
    }

    t_node_bool_array *result = (t_node_bool_array*)malloc(sizeof(*result));
    if (!result) { cleanup_tmp(nodes, vals, lis, prev); return NULL; }

    result->items = (t_node_bool*)calloc((size_t)best_len, sizeof(t_node_bool));
    if (!result->items) { free(result); cleanup_tmp(nodes, vals, lis, prev); return NULL; }

    size_t k = 0;
    for (int i = best_end; i != -1 && k < (size_t)best_len; i = prev[i]) {
        result->items[k].node  = nodes[i];
        result->items[k].value = true;
        ++k;
    }
    result->count = k;

    // Reverse the result array to get LIS in correct order
    for (size_t i = 0; i < result->count / 2; i++) {
        t_node_bool temp = result->items[i];
        result->items[i] = result->items[result->count - 1 - i];
        result->items[result->count - 1 - i] = temp;
    }

    cleanup_tmp(nodes, vals, lis, prev);
    return result;
}

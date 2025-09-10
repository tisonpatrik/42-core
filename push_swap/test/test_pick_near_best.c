#include "test_main.h"
#include "../include/selector.h"

// Include the generated test data arrays
#include "test_data_arrays.c"

// Helper function to create test data
static void create_test_data(t_sorting_state *state, int *stack_a, int stack_a_size, int *stack_b, int stack_b_size)
{
    // Clear existing stacks
    clear_stack(state->a);
    clear_stack(state->b);
    
    // Fill stack A
    for (int i = 0; i < stack_a_size; i++) {
        t_node *node = create_node(stack_a[i]);
        push_to_stack(state->a, node);
    }
    
    // Fill stack B
    for (int i = 0; i < stack_b_size; i++) {
        t_node *node = create_node(stack_b[i]);
        push_to_stack(state->b, node);
    }
}

// Helper function to parse array from string
static int parse_array(const char *str, int **array, int *size) {
    // Skip opening brace if present
    const char *start = str;
    if (*start == '{') {
        start++;
    }
    
    // Find closing brace to determine actual string length
    const char *end = start;
    while (*end && *end != '}') {
        end++;
    }
    
    // Count commas to determine size
    int count = 1;
    for (const char *p = start; p < end; p++) {
        if (*p == ',') count++;
    }
    
    *array = malloc(count * sizeof(int));
    if (!*array) return -1;
    
    *size = count;
    
    // Parse the string (skip braces)
    char *copy = malloc(end - start + 1);
    if (!copy) {
        free(*array);
        return -1;
    }
    strncpy(copy, start, end - start);
    copy[end - start] = '\0';
    
    char *token = strtok(copy, ",");
    int i = 0;
    
    while (token != NULL && i < count) {
        (*array)[i] = atoi(token);
        token = strtok(NULL, ",");
        i++;
    }
    
    free(copy);
    return 0;
}

// Helper function to parse expected position from string
static t_position parse_expected_position(const char *str) {
    t_position pos = {0};
    char *copy = strdup(str);
    char *token = strtok(copy, ":");
    
    if (token) pos.from_index = atoi(token);
    token = strtok(NULL, ":");
    if (token) pos.to_index = atoi(token);
    token = strtok(NULL, ":");
    if (token) pos.cost_a = atoi(token);
    token = strtok(NULL, ":");
    if (token) pos.cost_b = atoi(token);
    token = strtok(NULL, ":");
    if (token) pos.total = atoi(token);
    
    free(copy);
    return pos;
}

// Main test function that iterates through all test cases
void test_pick_near_best_operations(void)
{
    printf("Running PickNearBest tests...\n");
    
    const int num_test_cases = 40;
    int passed = 0;
    int failed = 0;
    
    // Iterate through all test cases
    for (int i = 0; i < num_test_cases; i++) {
        printf("Running test case %d... ", i);
        
        // Parse test data
        int *stack_a = NULL;
        int stack_a_size = 0;
        int *stack_b = NULL;
        int stack_b_size = 0;
        
        if (parse_array(stack_a_strings[i], &stack_a, &stack_a_size) != 0 ||
            parse_array(stack_b_strings[i], &stack_b, &stack_b_size) != 0) {
            printf("❌ Failed to parse test data\n");
            failed++;
            continue;
        }
        
        t_position expected_position = parse_expected_position(expected_positions[i]);
        
        // Create SortingState with empty stacks
        t_sorting_state *state = malloc(sizeof(t_sorting_state));
        if (!state) {
            printf("❌ Failed to allocate memory for sorting state\n");
            failed++;
            continue;
        }
        state->a = create_stack();
        state->b = create_stack();
        state->operations = NULL;
        if (!state->a || !state->b) {
            printf("❌ Failed to create stacks\n");
            if (state->a) free(state->a);
            if (state->b) free(state->b);
            free(state);
            failed++;
            continue;
        }
        
        // Populate stacks with test data
        create_test_data(state, stack_a, stack_a_size, stack_b, stack_b_size);
        
        // Act - Call PickNearBest with the test data
        t_position result = pick_near_best(state, max_candidates_values[i]);
        
        // Assert - Verify the result matches the expected position
        bool test_passed = true;
        if (result.from_index != expected_position.from_index) {
            printf("❌ FromIndex: expected %d, got %d\n", expected_position.from_index, result.from_index);
            test_passed = false;
        }
        if (result.to_index != expected_position.to_index) {
            printf("❌ ToIndex: expected %d, got %d\n", expected_position.to_index, result.to_index);
            test_passed = false;
        }
        if (result.cost_a != expected_position.cost_a) {
            printf("❌ CostA: expected %d, got %d\n", expected_position.cost_a, result.cost_a);
            test_passed = false;
        }
        if (result.cost_b != expected_position.cost_b) {
            printf("❌ CostB: expected %d, got %d\n", expected_position.cost_b, result.cost_b);
            test_passed = false;
        }
        if (result.total != expected_position.total) {
            printf("❌ Total: expected %d, got %d\n", expected_position.total, result.total);
            test_passed = false;
        }
        
        if (test_passed) {
            printf("✅ passed\n");
            passed++;
        } else {
            failed++;
        }
        
        // Cleanup
        free(stack_a);
        free(stack_b);
        free_sorting_state(state);
    }
    
    printf("\nTest Results: %d passed, %d failed out of %d total tests\n", passed, failed, num_test_cases);
}
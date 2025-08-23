
// Import the data structures and types from models.h
#include "../../libs/push_swap/src/models.h"
#include "../../include/generator.h"
#include "../../libs/cJSON/cJSON.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <time.h>  // Added for timestamp
#include <unistd.h> // Added for system calls

// Forward declaration of the function to test
t_stack	*loc_to_stack(t_ps *data, t_loc loc);

// Helper function to initialize a stack with random data
void init_stack(t_stack *stack, int size) {
    int *random_data = generate_random_array(size);
    stack->stack = random_data;
    stack->size = size;
    stack->top = 0;
    stack->bottom = size - 1;
}

// Helper function to free stack data
void cleanup_stack(t_stack *stack) {
    if (stack->stack) {
        free(stack->stack);
        stack->stack = NULL;
    }
}

// Helper function to create test data structure
t_ps* create_test_data(int stack_a_size, int stack_b_size) {
    t_ps *data = malloc(sizeof(t_ps));
    if (!data) return NULL;
    
    init_stack(&data->a, stack_a_size);
    init_stack(&data->b, stack_b_size);
    data->op_list = NULL;
    data->writing_mode = false;
    
    return data;
}

// Helper function to cleanup test data
void cleanup_test_data(t_ps *data) {
    if (data) {
        cleanup_stack(&data->a);
        cleanup_stack(&data->b);
        free(data);
    }
}

// Function to save results as JSON file
void save_results_to_json(t_ps *data, int test_results[4]) {
    cJSON *root = cJSON_CreateObject();
    
    // Create stack_a array
    cJSON *stack_a = cJSON_CreateArray();
    for (int i = 0; i < data->a.size; i++) {
        cJSON_AddItemToArray(stack_a, cJSON_CreateNumber(data->a.stack[i]));
    }
    cJSON_AddItemToObject(root, "stack_a", stack_a);
    
    // Create stack_b array
    cJSON *stack_b = cJSON_CreateArray();
    for (int i = 0; i < data->b.size; i++) {
        cJSON_AddItemToArray(stack_b, cJSON_CreateNumber(data->b.stack[i]));
    }
    cJSON_AddItemToObject(root, "stack_b", stack_b);
    
    // Create tests array
    cJSON *tests = cJSON_CreateArray();
    const char *locations[] = {"TOP_A", "BOTTOM_A", "TOP_B", "BOTTOM_B"};
    
    for (int i = 0; i < 4; i++) {
        cJSON *test = cJSON_CreateObject();
        cJSON_AddItemToObject(test, "id", cJSON_CreateNumber(i + 1));
        cJSON_AddItemToObject(test, "location", cJSON_CreateString(locations[i]));
        cJSON_AddItemToObject(test, "result", cJSON_CreateNumber(test_results[i]));
        cJSON_AddItemToArray(tests, test);
    }
    cJSON_AddItemToObject(root, "tests", tests);
    
    // Convert to string and save to file
    char *json_string = cJSON_Print(root);
    
    // Create data directory if it doesn't exist
    system("mkdir -p data");
    
    // Generate filename with timestamp
    char filename[100];
    time_t now = time(NULL);
    strftime(filename, sizeof(filename), "data/test_results_%Y%m%d_%H%M%S.json", localtime(&now));
    
    FILE *file = fopen(filename, "w");
    if (file) {
        fprintf(file, "%s", json_string);
        fclose(file);
        printf("Results saved to: %s\n", filename);
    } else {
        printf("Failed to save results to file\n");
    }
    
    // Cleanup
    free(json_string);
    cJSON_Delete(root);
}

// Modified test functions to return results instead of printing
int test_loc_to_stack_top_a(t_ps *data) {
    t_stack *result = loc_to_stack(data, TOP_A);
    return result->stack[result->top];
}

int test_loc_to_stack_bottom_a(t_ps *data) {
    t_stack *result = loc_to_stack(data, BOTTOM_A);
    return result->stack[result->bottom];
}

int test_loc_to_stack_top_b(t_ps *data) {
    t_stack *result = loc_to_stack(data, TOP_B);
    return result->stack[result->top];
}

int test_loc_to_stack_bottom_b(t_ps *data) {
    t_stack *result = loc_to_stack(data, BOTTOM_B);
    return result->stack[result->bottom];
}

int run_chunk_utils_tasks() {
    int size = 10;
	t_ps *data = create_test_data(size, size);
	if (!data) {
        printf("Failed to create test data\n");
        return 1;
    }
	
	// Run tests and collect results
    int test_results[4];
    test_results[0] = test_loc_to_stack_top_a(data);
    test_results[1] = test_loc_to_stack_bottom_a(data);
    test_results[2] = test_loc_to_stack_top_b(data);
    test_results[3] = test_loc_to_stack_bottom_b(data);
    
    // Save results to JSON file
    save_results_to_json(data, test_results);

    // Cleanup only once at the end
    cleanup_test_data(data);

    return 0;
}
#include "../../../libs/push_swap/src/models.h"
#include "../../../include/generator.h"
#include "../../../include/chunk_utils_task.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <time.h>
#include <unistd.h>
#include <string.h>

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

// Generic test case helper functions
t_test_case* create_test_case(int id, const char *name, int *input_array, int array_size, int result) {
    t_test_case *test = malloc(sizeof(t_test_case));
    if (!test) return NULL;
    
    test->id = id;
    test->name = strdup(name);
    test->input_array = malloc(array_size * sizeof(int));
    test->array_size = array_size;
    test->result = result;
    
    // Initialize optional parameters
    test->param1_name = NULL;
    test->param1_value = NULL;
    test->param2_name = NULL;
    test->param2_value = 0;
    test->param3_name = NULL;
    test->param3_value = NULL;
    
    // Copy input array
    if (test->input_array && input_array) {
        for (int i = 0; i < array_size; i++) {
            test->input_array[i] = input_array[i];
        }
    }
    
    return test;
}

void set_test_param1(t_test_case *test, const char *name, const char *value) {
    if (!test) return;
    if (test->param1_name) free(test->param1_name);
    if (test->param1_value) free(test->param1_value);
    test->param1_name = name ? strdup(name) : NULL;
    test->param1_value = value ? strdup(value) : NULL;
}

void set_test_param2(t_test_case *test, const char *name, int value) {
    if (!test) return;
    if (test->param2_name) free(test->param2_name);
    test->param2_name = name ? strdup(name) : NULL;
    test->param2_value = value;
}

void set_test_param3(t_test_case *test, const char *name, const char *value) {
    if (!test) return;
    if (test->param3_name) free(test->param3_name);
    if (test->param3_value) free(test->param3_value);
    test->param3_name = name ? strdup(name) : NULL;
    test->param3_value = value ? strdup(value) : NULL;
}

void free_test_case(t_test_case *test) {
    if (test) {
        if (test->name) free(test->name);
        if (test->input_array) free(test->input_array);
        if (test->param1_name) free(test->param1_name);
        if (test->param1_value) free(test->param1_value);
        if (test->param2_name) free(test->param2_name);
        if (test->param3_name) free(test->param3_name);
        if (test->param3_value) free(test->param3_value);
        free(test);
    }
}

t_test_batch* create_test_batch(const char *test_type, int num_tests) {
    t_test_batch *batch = malloc(sizeof(t_test_batch));
    if (!batch) return NULL;
    
    batch->test_type = strdup(test_type);
    batch->num_tests = num_tests;
    batch->tests = calloc(num_tests, sizeof(t_test_case));
    
    return batch;
}

void add_test_to_batch(t_test_batch *batch, int index, t_test_case *test) {
    if (batch && batch->tests && index >= 0 && index < batch->num_tests && test) {
        // Deep copy the test case
        batch->tests[index].id = test->id;
        batch->tests[index].name = test->name ? strdup(test->name) : NULL;
        batch->tests[index].array_size = test->array_size;
        batch->tests[index].result = test->result;
        
        // Copy array
        if (test->input_array && test->array_size > 0) {
            batch->tests[index].input_array = malloc(test->array_size * sizeof(int));
            if (batch->tests[index].input_array) {
                for (int i = 0; i < test->array_size; i++) {
                    batch->tests[index].input_array[i] = test->input_array[i];
                }
            }
        } else {
            batch->tests[index].input_array = NULL;
        }
        
        // Copy parameters
        batch->tests[index].param1_name = test->param1_name ? strdup(test->param1_name) : NULL;
        batch->tests[index].param1_value = test->param1_value ? strdup(test->param1_value) : NULL;
        batch->tests[index].param2_name = test->param2_name ? strdup(test->param2_name) : NULL;
        batch->tests[index].param2_value = test->param2_value;
        batch->tests[index].param3_name = test->param3_name ? strdup(test->param3_name) : NULL;
        batch->tests[index].param3_value = test->param3_value ? strdup(test->param3_value) : NULL;
    }
}

void free_test_batch(t_test_batch *batch) {
    if (batch) {
        if (batch->test_type) free(batch->test_type);
        if (batch->tests) {
            for (int i = 0; i < batch->num_tests; i++) {
                // Free individual test case members (not the struct itself)
                if (batch->tests[i].name) free(batch->tests[i].name);
                if (batch->tests[i].input_array) free(batch->tests[i].input_array);
                if (batch->tests[i].param1_name) free(batch->tests[i].param1_name);
                if (batch->tests[i].param1_value) free(batch->tests[i].param1_value);
                if (batch->tests[i].param2_name) free(batch->tests[i].param2_name);
                if (batch->tests[i].param3_name) free(batch->tests[i].param3_name);
                if (batch->tests[i].param3_value) free(batch->tests[i].param3_value);
            }
            free(batch->tests);
        }
        free(batch);
    }
}

#include "../../include/chunk_utils_task.h"
#include "../../include/stack_utils.h"
#include "../../libs/push_swap/src/models.h"
#include <stdlib.h>
#include <string.h>

// Test data creation utility
t_ps* create_test_data(int stack_a_size, int stack_b_size) {
    t_ps *data = malloc(sizeof(t_ps));
    if (!data) return NULL;
    
    init_stack(&data->a, stack_a_size);
    init_stack(&data->b, stack_b_size);
    data->op_list = NULL;
    data->writing_mode = false;
    
    return data;
}

// Test data cleanup utility
void cleanup_test_data(t_ps *data) {
    if (data) {
        cleanup_stack(&data->a);
        cleanup_stack(&data->b);
        free(data);
    }
}

// Generic test case creation utility
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

// Test parameter setting utilities
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

// Test case cleanup utility
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

// Test batch creation utility
t_test_batch* create_test_batch(const char *test_type, int num_tests) {
    t_test_batch *batch = malloc(sizeof(t_test_batch));
    if (!batch) return NULL;
    
    batch->test_type = strdup(test_type);
    batch->num_tests = num_tests;
    batch->tests = calloc(num_tests, sizeof(t_test_case));
    
    return batch;
}

// Helper function to copy test case basic data
static void copy_test_basic_data(t_test_case *dest, const t_test_case *src) {
    dest->id = src->id;
    dest->name = src->name ? strdup(src->name) : NULL;
    dest->array_size = src->array_size;
    dest->result = src->result;
}

// Helper function to copy test case array
static void copy_test_array(t_test_case *dest, const t_test_case *src) {
    if (src->input_array && src->array_size > 0) {
        dest->input_array = malloc(src->array_size * sizeof(int));
        if (dest->input_array) {
            for (int i = 0; i < src->array_size; i++) {
                dest->input_array[i] = src->input_array[i];
            }
        }
    } else {
        dest->input_array = NULL;
    }
}

// Helper function to copy test case parameters
static void copy_test_parameters(t_test_case *dest, const t_test_case *src) {
    dest->param1_name = src->param1_name ? strdup(src->param1_name) : NULL;
    dest->param1_value = src->param1_value ? strdup(src->param1_value) : NULL;
    dest->param2_name = src->param2_name ? strdup(src->param2_name) : NULL;
    dest->param2_value = src->param2_value;
    dest->param3_name = src->param3_name ? strdup(src->param3_name) : NULL;
    dest->param3_value = src->param3_value ? strdup(src->param3_value) : NULL;
}

// Test batch management utilities
void add_test_to_batch(t_test_batch *batch, int index, t_test_case *test) {
    if (!batch || !batch->tests || index < 0 || index >= batch->num_tests || !test) {
        return;
    }
    
    // Copy test case data using helper functions
    copy_test_basic_data(&batch->tests[index], test);
    copy_test_array(&batch->tests[index], test);
    copy_test_parameters(&batch->tests[index], test);
}

// Helper function to free individual test case members
static void free_test_case_members(t_test_case *test) {
    if (test->name) free(test->name);
    if (test->input_array) free(test->input_array);
    if (test->param1_name) free(test->param1_name);
    if (test->param1_value) free(test->param1_value);
    if (test->param2_name) free(test->param2_name);
    if (test->param3_name) free(test->param3_name);
    if (test->param3_value) free(test->param3_value);
}

// Test batch cleanup utility
void free_test_batch(t_test_batch *batch) {
    if (!batch) return;
    
    if (batch->test_type) free(batch->test_type);
    
    if (batch->tests) {
        for (int i = 0; i < batch->num_tests; i++) {
            free_test_case_members(&batch->tests[i]);
        }
        free(batch->tests);
    }
    
    free(batch);
}

#ifndef CHUNK_UTILS_TASK_H
# define CHUNK_UTILS_TASK_H

// Function declarations for chunk utils test suite
int run_chunk_utils_tasks(void);

// Test function declarations (if you want to expose them for external testing)
void test_loc_to_stack_basic_functionality(void);
void test_loc_to_stack_empty_stacks(void);
void test_loc_to_stack_single_element(void);
void test_loc_to_stack_large_stacks(void);
void test_loc_to_stack_mixed_sizes(void);
void test_loc_to_stack_rapid_calls(void);
void test_loc_to_stack_integration_chunks(void);
void test_loc_to_stack_boundary_values(void);

#endif // CHUNK_UTILS_TASK_H

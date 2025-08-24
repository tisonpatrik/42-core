#ifndef SET_SPLIT_LOC_TEST_H
# define SET_SPLIT_LOC_TEST_H

#include <stdbool.h>

// Forward declaration - models.h is already included in the .c file
struct s_push_swap;
typedef struct s_push_swap t_ps;

// Structure for set_split_loc test
typedef struct s_set_split_loc_test {
    int id;
    char *name;
    char *input_loc;
    char *min_loc_result;
    char *mid_loc_result;
    char *max_loc_result;
} t_set_split_loc_test;

// Function declarations
t_set_split_loc_test* create_set_split_loc_test(int id, const char *name, 
                                               const char *input_loc,
                                               const char *min_loc_result, 
                                               const char *mid_loc_result, 
                                               const char *max_loc_result);
void free_set_split_loc_test(t_set_split_loc_test *test);

#endif

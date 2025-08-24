#ifndef INNIT_SIZE_TEST_H
# define INNIT_SIZE_TEST_H

#include <stdbool.h>

// Forward declaration - models.h is already included in the .c file
struct s_push_swap;
typedef struct s_push_swap t_ps;

// Structure for innit_size test
typedef struct s_innit_size_test {
    int id;
    char *name;
    int min_size_before;
    int mid_size_before;
    int max_size_before;
    int min_size_after;
    int mid_size_after;
    int max_size_after;
} t_innit_size_test;

// Function declarations
t_innit_size_test* create_innit_size_test(int id, const char *name, 
                                         int min_size_before, int mid_size_before, int max_size_before,
                                         int min_size_after, int mid_size_after, int max_size_after);
void free_innit_size_test(t_innit_size_test *test);

#endif

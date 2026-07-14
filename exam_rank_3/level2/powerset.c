#include <stdio.h>
#include <stdlib.h>

/* Prints the current valid subset according to formatting rules */
void print_subset(int *subset, int size)
{
    if (size == 0)
    {
        printf("\n");
        return;
    }

    int i = 0;
    while (i < size)
    {
        printf("%d", subset[i]);
        if (i < size - 1)
            printf(" ");
        i++;
    }
    printf("\n");
}

/* Recursive backtracking function exploring all combinations */
void backtrack(int *set, int *subset, int set_size, int subset_size,
               int index, int current_sum, int target, int *found)
{
    // Base case: all elements evaluated
    if (index == set_size)
    {
        if (current_sum == target)
        {
            print_subset(subset, subset_size);
            *found = 1;
        }
        return;
    }

    /*
     * DECISION 1: Do NOT include the current element.
     * This branch runs first to perfectly match the example output order.
     */
    backtrack(set, subset, set_size, subset_size, index + 1, current_sum, target, found);

    /*
     * DECISION 2: DO include the current element.
     */
    subset[subset_size] = set[index];
    backtrack(set, subset, set_size, subset_size + 1, index + 1,
              current_sum + set[index], target, found);
}

/* Validates that all arguments are properly formatted numbers */
int check_args(int argc, char **argv)
{
    int i = 1;
    while (i < argc)
    {
        int j = 0;
        if (argv[i][j] == '+' || argv[i][j] == '-')
            j++;
        if (!argv[i][j]) // Single "+" or "-" is invalid
            return 0;
        while (argv[i][j])
        {
            if (argv[i][j] < '0' || argv[i][j] > '9')
                return 0;
            j++;
        }
        i++;
    }
    return 1;
}

int main(int argc, char **argv)
{
    // If no target is passed, print a newline and exit gracefully
    if (argc < 2)
    {
        printf("\n");
        return 0;
    }

    if (!check_args(argc, argv))
        return 1;

    int target = atoi(argv[1]);
    int set_size = argc - 2;

    // Guard against implementation-defined malloc(0) by allocating at least 1 element
    int alloc_size = (set_size > 0) ? set_size : 1;
    int *set = malloc(alloc_size * sizeof(int));
    int *subset = malloc(alloc_size * sizeof(int));

    if (!set || !subset)
    {
        free(set);
        free(subset);
        return 1;
    }

    // Fill the initial set array
    int i = 0;
    while (i < set_size)
    {
        set[i] = atoi(argv[i + 2]);
        i++;
    }

    int found = 0;

    // Execute backtracking
    backtrack(set, subset, set_size, 0, 0, 0, target, &found);

    // If absolutely no matching subsets were found, print a single empty line
    if (!found)
        printf("\n");

    free(set);
    free(subset);
    return 0;
}

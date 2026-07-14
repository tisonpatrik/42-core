#include <unistd.h>
#include <stdlib.h>

int ft_strlen(char *s)
{
    int i = 0;
    while (s[i])
        i++;
    return i;
}

void ft_swap(char *a, char *b)
{
    char temp = *a;
    *a = *b;
    *b = temp;
}

/* Sorts the string alphabetically (ASCII order) using Bubble Sort */
void sort_string(char *s, int len)
{
    int swapped = 1;
    while (swapped)
    {
        swapped = 0;
        int i = 0;
        while (i < len - 1)
        {
            if (s[i] > s[i + 1])
            {
                ft_swap(&s[i], &s[i + 1]);
                swapped = 1;
            }
            i++;
        }
    }
}

/* Backtracking using 'used' array to track indices */
void solve(char *source, char *result, int *used, int pos, int len)
{
    if (pos == len)
    {
        write(1, result, len);
        write(1, "\n", 1);
        return;
    }

    for (int i = 0; i < len; i++)
    {
        if (!used[i])
        {
            used[i] = 1;               // Mark index as used
            result[pos] = source[i];   // Place character
            solve(source, result, used, pos + 1, len);
            used[i] = 0;               // Backtrack (unmark)
        }
    }
}

int main(int argc, char **argv)
{
    // If invalid argument count, 42 standard is to print a newline and exit
    if (argc != 2)
    {
        write(1, "\n", 1);
        return 0;
    }

    int len = ft_strlen(argv[1]);

    // Edge case: Empty string should just print a newline
    if (len == 0)
    {
        write(1, "\n", 1);
        return 0;
    }

    // Safely copy argv[1] to a modifiable heap buffer
    char *source = malloc(len + 1);
    if (!source)
        return 1;
    for (int i = 0; i <= len; i++)
        source[i] = argv[1][i];

    // Sort the copied string to guarantee alphabetical permutations
    sort_string(source, len);

    // Allocate result buffer and initialize used array
    char *result = malloc(len + 1);
    int *used = calloc(len, sizeof(int));

    if (!result || !used)
    {
        free(source);
        free(result);
        free(used);
        return 1;
    }
    result[len] = '\0';

    // Start generating permutations
    solve(source, result, used, 0, len);

    // Clean up
    free(source);
    free(result);
    free(used);
    return 0;
}

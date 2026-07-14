#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <float.h>

typedef struct s_city
{
    float x;
    float y;
}    t_city;

/*
** Returns the Euclidean distance between 2 cities using sqrtf
*/
float    distance(t_city a, t_city b)
{
    float dx = a.x - b.x;
    float dy = a.y - b.y;
    return sqrtf(dx * dx + dy * dy);
}

/*
** Computes total distance of the closed loop path
*/
float    total_distance(t_city *cities, int *path, int n)
{
    float dist = 0.0f;
    for (int i = 0; i < n - 1; i++)
    {
        dist += distance(cities[path[i]], cities[path[i + 1]]);
    }
    // Return to the starting city
    dist += distance(cities[path[n - 1]], cities[path[0]]);
    return dist;
}

/*
** Backtracking algorithm to try all permutations
*/
void    solve(t_city *cities, int *path, int n, int pos, float *min)
{
    // Base case: we have a complete permutation
    if (pos == n - 1)
    {
        float cur_dist = total_distance(cities, path, n);
        if (cur_dist < *min)
            *min = cur_dist;
        return;
    }

    for (int i = pos; i < n; i++)
    {
        // Swap path[pos] and path[i]
        int temp = path[pos];
        path[pos] = path[i];
        path[i] = temp;

        // Recursive call for the next position
        solve(cities, path, n, pos + 1, min);

        // Backtrack (Swap back to restore original state)
        temp = path[pos];
        path[pos] = path[i];
        path[i] = temp;
    }
}

int    main(void)
{
    t_city    cities[11];
    int        n = 0;

    // Read input from stdin using fscanf
    while (n < 11 && fscanf(stdin, "%f, %f", &cities[n].x, &cities[n].y) == 2)
        n++;

    // If less than 2 cities → distance is 0.00
    if (n < 2)
    {
        fprintf(stdout, "0.00\n"); // OPRAVA: Použit fprintf namísto printf
        return (0);
    }

    // Initialize path array: [0, 1, 2, ..., n-1]
    int path[11];
    for (int i = 0; i < n; i++)
        path[i] = i;

    float min = FLT_MAX;

    /*
    ** Optimization: Fix the first city at index 0.
    ** Permute only from position 1 onwards to avoid redundant rotation checks.
    */
    solve(cities, path, n, 1, &min);

    fprintf(stdout, "%.2f\n", min); // OPRAVA: Použit fprintf namísto printf
    return (0);
}

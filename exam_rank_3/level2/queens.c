#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>

#define MAX 2048

void print_solution(int board[], int n)
{
    for (int i = 0; i < n; i++)
    {
        fprintf(stdout, "%d", board[i]);
        if (i < n -1)
            fprintf(stdout, " ");
    }
    fprintf(stdout, "\n");
}


bool is_match(int board[], int col, int test_row)
{
    for (int prev_col = 0; prev_col < col; prev_col++)
    {
        int row = board[prev_col];
        if (row == test_row)
            return false;
        int distance = col - prev_col;
        if ( test_row == row - distance)
            return false;
        if ( test_row == row + distance)
            return false;
    }
    return true;
}

void solve(int board[], int cur_col, int n)
{
    if(cur_col == n)
    {
        print_solution(board, n);
        return;
    }

    for(int row = 0; row < n; row ++)
    {
        if (is_match(board, cur_col, row))
        {
            board[cur_col] = row;
            solve(board, cur_col + 1, n);
        }
    }
}


int main (int ac, char* av[])
{
    if(ac == 2 && av[1] != NULL)
    {
        int n = atoi(av[1]);
        if ( 0 < n && n < MAX)
        {
            int board[MAX];
            solve(board, 0, n);
        }
    }
    return 0;
}

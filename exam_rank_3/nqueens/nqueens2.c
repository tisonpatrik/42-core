
#include<stdlib.h>
#include<stdio.h>
#include<stdbool.h>

void print_solution(int board[], int n)
{
    int idx = 0;
    while(idx < n)
    {
        fprintf(stdout, "%d", board[idx]);
        if (idx < n-1)
            fprintf(stdout, " ");
        idx++;
    }
    fprintf(stdout, "\n");
}


bool is_position_safe(int board[], int col, int test_row)
{
    int prev_col =0;
    while(prev_col < col)
    {
        int row = board[prev_col];
        if (row == test_row)
            return false;
        int distance = col - prev_col;
        if (test_row == row - distance)
            return false;
        if(test_row == row + distance)
            return false;
        prev_col++;
    }
    return true;
}


int find_safe_position_on_row(int board[],int col, int start_row, int n)
{
    int row = start_row;
    while(row < n)
    {
        if (is_position_safe(board, col, row))
            return row;
        row++;
    }
    return -1;
}

void solve(int max, int n)
{
    int board[max];
    int col = 0;
    board[col] =0;

    while( col >=0)
    {
        int row_to_try = board[col];
        int safe_position = find_safe_position_on_row(board, col, row_to_try, n);
        
        bool is_safe_pos = (safe_position != -1);
        bool is_last_col = (col == n-1);
        
        if (is_safe_pos && is_last_col)
        {
            board[col]= safe_position;
            print_solution(board, n);
            board[col]++;
        }
        else if (is_safe_pos && !is_last_col){
            board[col]=safe_position;
            col++;
            board[col] = 0;
        }
        else{
            col--;
            board[col]++;
        }
    }
}


int main (int ac, char* ag[])
{
    int max = 100;
    if (ac == 2)
    {
        int n = atoi(ag[1]);
        if (n > 0 && n < max)
            solve(max, n);
    }
    return 0;
}

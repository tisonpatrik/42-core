#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


void print_board(int board[], int n)
{
	int i = 0;
	while(i < n)
	{
		fprintf(stdout,"%d", board[i]);
		if(i < n -1 )
			fprintf(stdout," ");
		i++;
	}
	fprintf(stdout,"\n");
}

bool is_safe_position(int board[], int col, int test_row)
{
	for(int prev_col = 0; prev_col < col; prev_col++)
	{
		int prev_row = board[prev_col];
		if (prev_row == test_row)
			return false;
		int distance = col - prev_col;
		if(test_row == prev_row - distance)
			return false;
		if(test_row == prev_row + distance)
			return false;
	}
	return true;
}

void solve(int board[], int current_col, int n)
{
	if(current_col == n)
	{
		print_board(board, n);
		return;;
	}
	
	for(int row = 0; row < n; row++)
	{
		if(is_safe_position(board, current_col, row))
		{
			board[current_col]= row;
			solve(board, current_col + 1, n);
		}
	}

}

int main(int ac, char* av[])
{
	if(ac ==2)
	{
		int max = 1024;
		int n = atoi(av[1]);
		if(n > 0 && n < max)
		{
			int board[max];
			solve(board, 0, n);
		}
	}
	return 0;
}

#include <stdbool.h>
#include <unistd.h>

#define MAX 2048

/* Custom putchar using allowed write function */
void ft_putchar(char c)
{
    write(1, &c, 1);
}

/* Custom putnbr to print indices without using printf */
void ft_putnbr(int n)
{
    if (n >= 10)
        ft_putnbr(n / 10);
    ft_putchar((n % 10) + '0');
}

/* Simple atoi in case the standard one is forbidden */
int ft_atoi(const char *str)
{
    int res = 0;
    int i = 0;
    while (str[i] >= '0' && str[i] <= '9')
    {
        res = res * 10 + (str[i] - '0');
        i++;
    }
    return res;
}

void print_board(int board[], int n)
{
    int i = 0;
    while (i < n)
    {
        /* OPRAVA: Přičítáme + 1 pro 1-based indexování */
        ft_putnbr(board[i] + 1);
        if (i < n - 1)
            ft_putchar(' ');
        i++;
    }
    ft_putchar('\n');
}

bool is_match(int board[], int col, int test_row)
{
    for (int prev_col = 0; prev_col < col; prev_col++)
    {
        int row = board[prev_col];
        if (row == test_row)
            return false;

        int distance = col - prev_col;

        if (test_row == row - distance)
            return false;
        if (test_row == row + distance)
            return false;
    }
    return true;
}

void solve(int board[], int cur_col, int n)
{
    if (cur_col == n)
    {
        print_board(board, n);
        return;
    }

    for (int row = 0; row < n; row++)
    {
        if (is_match(board, cur_col, row))
        {
            board[cur_col] = row;
            solve(board, cur_col + 1, n);
        }
    }
}

int main(int ac, char* av[])
{
    if (ac == 2)
    {
        int n = ft_atoi(av[1]);
        if (n > 0 && n < MAX)
        {
            int board[MAX];
            solve(board, 0, n);
        }
    }
    return 0;
}

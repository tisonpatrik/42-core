#include <unistd.h>
#include <stdbool.h>

bool is_balanced(char* str)
{
    int balance = 0;
    for (int i = 0; str[i]; i++)
    {
        if (str[i] == '(')
            balance++;
        else if (str[i] == ')')
        {
            balance--;
            if (balance < 0)
                return false;
        }
    }
    return (balance == 0);
}

/* Prints the string exactly as is, keeping the spaces */
void print_solution(char* str)
{
    int i = 0;
    while (str[i])
    {
        write(1, &str[i], 1);
        i++;
    }
    write(1, "\n", 1);
}

void solve(char* str, int start, int left, int right)
{
    if (left == 0 && right == 0)
    {
        if (is_balanced(str))
            print_solution(str);
        return;
    }

    for (int i = start; str[i]; i++)
    {
        char c = str[i];
        if (c == '(' && left > 0)
        {
            str[i] = ' ';
            solve(str, i + 1, left - 1, right);
            str[i] = '(';
        }
        else if (c == ')' && right > 0)
        {
            str[i] = ' ';
            solve(str, i + 1, left, right - 1);
            str[i] = ')';
        }
    }
}

int main(int ac, char* av[])
{
    // If arguments are wrong, standard 42 behavior is printing a newline
    if (ac != 2)
    {
        write(1, "\n", 1);
        return 0;
    }

    char* str = av[1];
    int left = 0;
    int right = 0;

    for (int i = 0; str[i]; i++)
    {
        if (str[i] == '(')
            left++;
        else if (str[i] == ')')
        {
            if (left > 0)
                left--;
            else
                right++;
        }
        else
        {
            write(1, "\n", 1);
            return 0;
        }
    }

    solve(str, 0, left, right);
    return 0;
}

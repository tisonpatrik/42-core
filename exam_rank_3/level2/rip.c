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

/* Prints the string, skipping the spaces (removed parentheses) */
void print_clean(char* str)
{
    for (int i = 0; str[i]; i++)
    {
        if (str[i] != ' ')
            write(1, &str[i], 1);
    }
    write(1, "\n", 1);
}

void solve(char* str, int start, int left, int right)
{
    if (left == 0 && right == 0)
    {
        if (is_balanced(str))
            print_clean(str);
        return;
    }

    for (int i = start; str[i]; i++)
    {
        // Skip duplicates to guarantee unique output combinations
        if (i > start && str[i] == str[i - 1])
            continue;

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
    // Clean and safe argument check
    if (ac != 2 || av[1][0] == '\0')
        return 1;

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
            return 1; // Reject any invalid characters
        }
    }

    solve(str, 0, left, right);
    return 0;
}

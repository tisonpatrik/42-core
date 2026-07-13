#include <unistd.h>
#include <stdbool.h>

int ft_strlen(char* str)
{
    int i = 0;
    while(str[i])
        i++;
    return i;
}

bool is_balanced(char* str)
{
    int balance = 0;
    for(int i = 0; str[i]; i++)
    {
        if(str[i] == '(')
            balance++;
        else if(str[i] == ')')
        {
            balance--;
            if(balance < 0)
                return 0;
        }
    }
    return (balance == 0);
}

void ft_putstr_nl(char* str)
{
    write(1, str, ft_strlen(str));
    write(1, "\n", 1);
}

void solve(char* str, int idx, int left, int right)
{
    if (left == 0 && right == 0)
    {
        if (is_balanced(str))
            ft_putstr_nl(str);
        return;
    }
    
    while(str[idx])
    {
        char c = str[idx];
        if (c == '(' && left > 0)
        {
            str[idx] = ' ';
            solve(str, idx + 1, left - 1, right);
            str[idx] = '(';
        }
        else if (c == ')' && right > 0)
        {
            str[idx] = ' ';
            solve(str, idx + 1, left, right - 1);
            str[idx] = ')';
        }
        idx++;
    }
}

int main(int ac, char* av[])
{
    if(ac != 2 || !av[0] || av[1][0]=='\0')
        return 1;

    char* str = av[1];
    int left = 0;
    int right = 0;

    for(int i = 0; str[i]; i++)
    {
        if(str[i] == '(')
            left++;
        else if(str[i] == ')')
        {
            if(left > 0)
                left--;
            else
                right++;
        }
        else
        {
            return 1;
        }
    }
    solve(str, 0, left, right);

    return 0;
}

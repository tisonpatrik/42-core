#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

#define MAX 4048

int read_input(char* input)
{
    ssize_t bytes;
    int total_read;
    while((bytes = read(0, input + total_read, MAX - total_read)) > 0)
    {
        total_read+=bytes;
    }
    if (total_read == -1)
    {
        return total_read;
    }

    input[total_read] = '\0';
    return total_read;
}

bool is_match(char* input, char* pattern, int p_len)
{
    int i = 0;
    while(i < p_len)
    {
        if (input[i]!= pattern[i])
            return false;
        i++;
    }
    return true;
}

void print_stars(int len)
{
    int i = 0;
    while(i < len)
    {
        printf("*");
        i++;
    }
}

void process_input(char* pattern, int p_len, char* input, int i_len)
{
    int i = 0;
    while(i < i_len)
    {
        if(is_match(&input[i], pattern, p_len))
        {
            print_stars(p_len);
            i += p_len;
        }
        else {
            printf("%c", input[i]);
            i++;
        }
    }
}

int main (int ag, char* av[])
{
    if(ag != 2 || !av[1] || av[1][0] == '\0')
    {
        return 1;
    }
    char* pattern = av[1];
    int p_len = strlen(pattern);
    char* input = malloc(MAX + 1);
    if (!input)
    {
        perror("Error");
        free(input);
        return 1;
    }

    int i_len = read_input(input);

    if(i_len == -1)
    {
        perror("Error");
        free(input);
        return 1;
    }

    process_input(pattern, p_len, input, i_len);

    free(input);
    return 0;

}

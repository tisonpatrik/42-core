#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main(int ac, char* av[])
{
    if (ac != 2 || av[1] == NULL || strlen(av[1]) == 0)
    {
        return 1;
    }

    int len = strlen(av[1]);

    char* buffer = malloc(len + 1);

    if (!buffer)
    {
        fprintf(stderr, "Error: malloc failed\n");
        return 1;
    }

    int i = 0;
    char c;

    while (read(0, &c, 1) > 0)
    {
        if (av[1][i] == c)
        {
            buffer[i] = c;
            i++;
            if (i == len)
            {
                int j = 0;
                while(j < len)
                {
                    printf("*");
                    j++;
                }
                i = 0;
            }
        }
        else
        {
            buffer[i] = '\0';
            printf("%s", buffer);

            i = 0;

            if (c == av[1][i])
            {
                buffer[0] = c;
                i = 1;
            }
            else
            {
                printf("%c", c);
            }
        }
    }

    if (i > 0)
    {
        buffer[i] = '\0';
        printf("%s", buffer);
    }

    free(buffer);
    return 0;
}

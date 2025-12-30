#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
    if (argc != 2 || argv[1][0] == '\0')
    {
        return 1;
    }

    char *pattern = argv[1];
    int pattern_len = (int)strlen(pattern);
    char *match_buffer = malloc(pattern_len + 1);

    if (!match_buffer)
    {
        perror("Error");
        return EXIT_FAILURE;
    }

    char c;
    int i = 0;
    ssize_t bytes_read;

    while ((bytes_read = read(STDIN_FILENO, &c, 1)) > 0)
    {
        if (c == pattern[i])
        {
            match_buffer[i] = c;
            i++;
            if (i == pattern_len)
            {
                int j = 0;
                while (j < pattern_len)
                {
                    printf("*");
                    j++;
                }
                i = 0;
            }
        }
        else
        {
            if (i > 0)
            {
                match_buffer[i] = '\0';
                printf("%s", match_buffer);
                i = 0;
            }
            if (c == pattern[i])
            {
                match_buffer[i] = c;
                i = 1;
            }
            else
            {
                printf("%c", c);
            }
        }
    }

    if (bytes_read == -1)
    {
        perror("Error");
        free(match_buffer);
        return EXIT_FAILURE;
    }

    if (i > 0)
    {
        match_buffer[i] = '\0';
        printf("%s", match_buffer);
    }

    free(match_buffer);
    return EXIT_SUCCESS;
}

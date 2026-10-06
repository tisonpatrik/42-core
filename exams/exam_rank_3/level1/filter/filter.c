#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define BUF_SIZE 2048

void print_stars(int len)
{
    for (int i = 0; i < len; i++)
    {
        write(1, "*", 1);
    }
}

int main(int ac, char* av[])
{
    if(ac != 2 || av[1] == NULL || av[1][0]=='\0')
    {
        return 1;
    }

    char* pattern = av[1];
    ssize_t p_len = strlen(pattern);

    char* buf = malloc(BUF_SIZE + 1);
    if (!buf)
    {
        perror("Error");
        return 1;
    }

    ssize_t bytes;
    ssize_t current_len = 0;

    while ((bytes = read(0, buf + current_len, BUF_SIZE- current_len)) > 0) {
        current_len += bytes;
        char* match;
        while((match = memmem(buf, current_len, pattern, p_len)) != NULL)
        {
            write(1, buf, match - buf);
            print_stars(p_len);
            ssize_t consumed = (match - buf) + p_len;
            ssize_t remaining  = current_len - consumed;
            memmove(buf, buf + consumed,remaining);
            current_len = remaining;
        }
        if (current_len > p_len)
        {
            ssize_t safe_to_write = current_len - (p_len - 1);
            write(1, buf, safe_to_write);
            memmove(buf, buf + safe_to_write, current_len - safe_to_write);
            current_len -= safe_to_write;
        }
    }

    if(bytes == -1)
    {
        perror("Error");
        free(buf);
        return 1;
    }
    if (current_len > 0)
        write(1, buf, current_len);

    free(buf);
    return 0;
}

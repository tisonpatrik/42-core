#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>

bool is_match(const char *buf, const char *pattern, int len)
{
    int i = 0;
    while(i < len)
    {
        if (buf[i] != pattern[i])
        {
            return false;
        }
        i++;
    }
    return true;
}

void shift_window(char *buf, int len)
{
    int i = 0;
    while(i<len)
    {
        buf[i] = buf[i + 1];
        i++;
    }
}

void print_stars(int count)
{
    int i = 0;
    while( i < count)
    {
        printf("*");
        i++;
    }
}

void print_buffer(char* buf, int len)
{
    int i = 0;
    while(i<len)
    {
        printf("%c", buf[i]);
        i++;
    }
}

int main(int argc, char *argv[])
{
    if (argc != 2 || argv[1][0] == '\0')
        return 1;

    char *pattern = argv[1];
    int p_len = strlen(pattern);
    char *buf = malloc(p_len);

    if (!buf)
    {
        perror("Error");
        return 1;
    }

    int buf_len = 0;
    char c;
    ssize_t bytes_read;

    while ((bytes_read = read(STDIN_FILENO, &c, 1)) > 0)
    {
        buf[buf_len++] = c;

        // Guard clause: Pokud buffer ještě není plný, přeskoč zbytek cyklu.
        // Tímto jsme smazali obrovské zanoření (arrow code).
        if (buf_len < p_len)
            continue;

        // Zpracování plného okna
        if (is_match(buf, pattern, p_len))
        {
            print_stars(p_len);
            buf_len = 0; // Vyprázdnění okna
        }
        else
        {
            printf("%c", buf[0]);
            shift_window(buf, p_len);
            buf_len--; // Zmenšení okna o 1, aby se udělalo místo v dalším cyklu
        }
    }

    // Ošetření případné chyby po skončení čtení
    if (bytes_read == -1)
    {
        perror("Error");
        free(buf);
        return 1;
    }


    print_buffer(buf, buf_len);

    free(buf);
    return 0;
}

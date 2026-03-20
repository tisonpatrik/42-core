#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

// --- Pomocné funkce ---

int is_match(const char *buf, const char *pattern, int len)
{
    for (int i = 0; i < len; i++)
    {
        if (buf[i] != pattern[i])
        {
            return 0; // Neshoda
        }
    }
    return 1; // Shoda
}

void shift_window(char *buf, int len)
{
    for (int i = 0; i < len - 1; i++)
    {
        buf[i] = buf[i + 1];
    }
}

void print_stars(int count)
{
    for (int i = 0; i < count; i++)
    {
        printf("*");
    }
}

// --- Hlavní program ---

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

    // Hlavní smyčka
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

    // Vyprázdnění zbytku bufferu na konci souboru (EOF)
    for (int i = 0; i < buf_len; i++)
    {
        printf("%c", buf[i]);
    }

    free(buf);
    return 0;
}

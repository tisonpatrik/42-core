#include "get_next_line.h"
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#ifndef BUFFER_SIZE
#endif

char *get_next_line(int fd)
{
    static char buffer[BUFFER_SIZE + 1];
    char *line = NULL;
    size_t line_len = 0;
    ssize_t bytes_read;

    if (fd < 0 || BUFFER_SIZE <= 0)
        return NULL;

    while (1)
    {
        // If buffer is empty, read into it
        if (buffer[0] == '\0')
        {
            bytes_read = read(fd, buffer, BUFFER_SIZE);
            if (bytes_read <= 0)
                break;
            buffer[bytes_read] = '\0';
        }

        // Find newline in buffer
        char *newline = strchr(buffer, '\n');
        size_t chunk_len = newline ? (size_t)(newline - buffer + 1) : strlen(buffer);

        // Allocate or expand line buffer
        char *new_line = malloc(line_len + chunk_len + 1);
        if (!new_line)
        {
            free(line);
            return NULL;
        }
        if (line)
        {
            memcpy(new_line, line, line_len);
            free(line);
        }
        memcpy(new_line + line_len, buffer, chunk_len);
        line_len += chunk_len;
        new_line[line_len] = '\0';
        line = new_line;

        // Move leftover buffer content to front
        if (newline)
        {
            memmove(buffer, buffer + chunk_len, strlen(buffer + chunk_len) + 1);
            break;
        }
        else
        {
            buffer[0] = '\0'; // All consumed, clear buffer
        }
    }
    if (line_len == 0)
    {
        free(line);
        return NULL;
    }
    return line;
}

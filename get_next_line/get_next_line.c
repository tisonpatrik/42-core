#include "get_next_line.h"
#include <stdlib.h>
#include <unistd.h>

void	*ft_realloc(void *ptr, size_t old_size, size_t new_size);

char *get_next_line(int fd)
{
    static char buffer[BUFFER_SIZE + 1];
    static size_t buffer_pos = 0;
    static size_t buffer_size = 0;
    char *line = NULL;
    size_t line_size = 0;
    size_t line_pos = 0;
    ssize_t bytes_read;

    if (fd < 0 || BUFFER_SIZE <= 0)
        return NULL;

    while (1)
    {
        // If buffer is empty or fully consumed, read more data
        if (buffer_pos >= buffer_size)
        {
            bytes_read = read(fd, buffer, BUFFER_SIZE);
            if (bytes_read <= 0)
                break;
            buffer_size = bytes_read;
            buffer_pos = 0;
        }

        // Find newline in remaining buffer
        size_t i = buffer_pos;
        while (i < buffer_size && buffer[i] != '\n')
            i++;

        // Calculate chunk size (include newline if found)
        size_t chunk_size = i - buffer_pos;
        if (i < buffer_size && buffer[i] == '\n')
            chunk_size++;

        // Reallocate line buffer if needed
        if (line_pos + chunk_size + 1 > line_size)
        {
            size_t new_size = line_size == 0 ? chunk_size + 1 : line_size * 2;
            if (new_size < line_pos + chunk_size + 1)
                new_size = line_pos + chunk_size + 1;
            
            char *new_line = ft_realloc(line, line_size, new_size);
            if (!new_line)
            {
                free(line);
                return NULL;
            }
            line = new_line;
            line_size = new_size;
        }

        // Copy chunk to line
        for (size_t j = 0; j < chunk_size; j++)
            line[line_pos + j] = buffer[buffer_pos + j];
        line_pos += chunk_size;
        line[line_pos] = '\0';

        // Update buffer position
        buffer_pos += chunk_size;

        // If we found a newline, we're done
        if (buffer_pos > 0 && buffer[buffer_pos - 1] == '\n')
            break;
    }

    return line;
}

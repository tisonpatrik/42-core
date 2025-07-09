#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

# include <stddef.h>

typedef struct s_buffer {
	char		data[BUFFER_SIZE + 1];
	size_t		pos;
	size_t		size;
}	t_buffer;

typedef struct s_line {
	char		*data;
	size_t		size;
	size_t		pos;
}	t_line;

char	*get_next_line(int fd);

#endif

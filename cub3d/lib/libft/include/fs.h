#ifndef FS_H
# define FS_H

# include "allocator.h"
# include "str8.h"

bool	ft_read_file(t_arena *arena, const char *filepath, t_str8 *file);

#endif

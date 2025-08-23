#ifndef CHUNK_UTILS_H
# define CHUNK_UTILS_H

#include "models.h"

// Chunk utility functions
t_stack *loc_to_stack(t_ps *data, t_loc loc);
int chunk_max_value(t_ps *data, t_chunk *chunk);
int chunk_value(t_ps *data, t_chunk *chunk, int n);

#endif

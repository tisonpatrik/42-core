#ifndef CHUNK_SPLIT_H
# define CHUNK_SPLIT_H

#include "models.h"

// Chunk split functions
void chunk_split(t_ps *data, t_chunk *to_split, t_split_dest *dest);
void innit_size(t_chunk *min, t_chunk *mid, t_chunk *max);
void set_split_loc(t_loc loc, t_chunk *min, t_chunk *mid, t_chunk *max);
void set_third_pivots(t_loc loc, int crt_size, int *pivot_1, int *pivot_2);

#endif

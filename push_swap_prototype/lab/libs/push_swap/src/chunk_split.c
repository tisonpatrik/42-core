#include "models.h"

void	innit_size(t_chunk *min, t_chunk *mid, t_chunk *max);
void	set_split_loc(t_loc loc, t_chunk *min, t_chunk *mid, t_chunk *max);
void	set_third_pivots(t_loc loc, int crt_size, int *pivot_1, int *pivot_2);
int	chunk_max_value(t_ps *data, t_chunk *chunk);
int	chunk_value(t_ps *data, t_chunk *chunk, int n);
int	move_from_to(t_ps *data, t_loc from, t_loc to);
void	split_max_reduction(t_ps *data, t_chunk *max);
bool	a_partly_sort(t_ps *data, int n);
void	easy_sort(t_ps *data, t_chunk *chunk);


void	chunk_split(t_ps *data, t_chunk *to_split, t_split_dest *dest)
{
	int	pivot_1;
	int	pivot_2;
	int	max_value;
	int	next_value;

	innit_size(&dest->min, &dest->mid, &dest->max);
	set_split_loc(to_split->loc, &dest->min, &dest->mid, &dest->max);
	set_third_pivots(to_split->loc, to_split->size, &pivot_1, &pivot_2);
	max_value = chunk_max_value(data, to_split);
	while (to_split->size--)
	{
		next_value = chunk_value(data, to_split, 1);
		if (next_value > max_value - pivot_2)
		{
			dest->max.size += move_from_to(data, to_split->loc, dest->max.loc);
			split_max_reduction(data, &dest->max);
			if (a_partly_sort(data, 1) && to_split->size)
				easy_sort(data, to_split);
		}
		else if (next_value > max_value - pivot_1)
			dest->mid.size += move_from_to(data, to_split->loc, dest->mid.loc);
		else
			dest->min.size += move_from_to(data, to_split->loc, dest->min.loc);
	}
}

void	innit_size(t_chunk *min, t_chunk *mid, t_chunk *max)
{
	min->size = 0;
	mid->size = 0;
	max->size = 0;
}

void	set_split_loc(t_loc loc, t_chunk *min, t_chunk *mid, t_chunk *max)
{
	if (loc == TOP_A)
	{
		min->loc = BOTTOM_B;
		mid->loc = TOP_B;
		max->loc = BOTTOM_A;
	}
	else if (loc == BOTTOM_A)
	{
		min->loc = BOTTOM_B;
		mid->loc = TOP_B;
		max->loc = TOP_A;
	}
	else if (loc == TOP_B)
	{
		min->loc = BOTTOM_B;
		mid->loc = BOTTOM_A;
		max->loc = TOP_A;
	}
	else if (loc == BOTTOM_B)
	{
		min->loc = TOP_B;
		mid->loc = BOTTOM_A;
		max->loc = TOP_A;
	}
}

void	set_third_pivots(t_loc loc, int crt_size, int *pivot_1, int *pivot_2)
{
	*pivot_2 = crt_size / 3;
	*pivot_1 = crt_size / 2; // Default initialization
	if (loc == TOP_A || loc == BOTTOM_A)
		*pivot_1 = 2 * crt_size / 3;
	if (loc == TOP_B || loc == BOTTOM_B)
		*pivot_1 = crt_size / 2;
	if ((loc == TOP_A || loc == BOTTOM_A) && crt_size < 15)
		*pivot_1 = crt_size;
	if (loc == BOTTOM_B && crt_size < 8)
		*pivot_2 = crt_size / 2;
}

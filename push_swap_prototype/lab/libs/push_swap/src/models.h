#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <limits.h>
#include <ctype.h>
#include <string.h>
#include <unistd.h>
#include <stdint.h>


typedef struct s_list
{
	void			*content;
	struct s_list	*next;
	struct s_list	*prev;
}					t_list;

typedef struct s_stack
{
	int		*stack;
	int		size;
	int		top;
	int		bottom;
}			t_stack;

typedef struct s_push_swap
{
	t_stack	a;
	t_stack	b;
	t_list	*op_list;
	bool	writing_mode;
}			t_ps;

typedef enum e_op
{
	null_op,
	pa,
	pb,
	ra,
	rb,
	rr,
	rra,
	rrb,
	rrr,
	sa,
	sb,
	ss
}			t_op;
typedef enum e_loc
{
	TOP_A,
	BOTTOM_A,
	TOP_B,
	BOTTOM_B
}			t_loc;

typedef struct s_chunk
{
	t_loc	loc;
	int		size;
}			t_chunk;

typedef struct s_split_dest
{
	t_chunk	min;
	t_chunk	mid;
	t_chunk	max;
}			t_split_dest;

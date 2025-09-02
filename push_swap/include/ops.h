#include "stack.h"
#include "../libft/include/libft.h"

typedef enum e_operation
{
    SA = 0,
    SB,
    SS,
    PA,
    PB,
    RA,
    RB,
    RR,
    RRA,
    RRB,
    RRR
} t_operation;

typedef struct s_sorting_state
{
    t_stack *a;
    t_stack *b;
    t_list *operations;
}				t_sorting_state;

// Function declarations
t_sorting_state *create_sorting_state(int *numbers, int n);
void free_sorting_state(t_sorting_state *state);
void save_operation(t_sorting_state *state, t_operation operation);

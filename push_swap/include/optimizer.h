
#ifndef OPTIMIZER_H
# define OPTIMIZER_H

# include "../libft/include/libft.h"
# include "ops.h"
# include <stdlib.h>
# include <stdbool.h>

typedef enum e_optimizer_error
{
	OPTIMIZER_SUCCESS = 0,
	OPTIMIZER_INVALID_INPUT,
	OPTIMIZER_MEMORY_ERROR,
	OPTIMIZER_ARENA_FULL,
	OPTIMIZER_INVALID_CONFIG
}				t_optimizer_error;

typedef struct s_optimizer_arena
{
	t_operation	*operations;
	t_list		**temp_lists;
	int			*indices;
	bool		*flags;
	size_t		capacity;
	size_t		used;
	void		*arena_memory;
	size_t		arena_size;
}				t_optimizer_arena;

typedef struct s_operation_builder
{
	t_optimizer_arena	*arena;
	t_list				*result;
	bool				changed;
	t_optimizer_error	error;
}						t_operation_builder;

typedef struct s_merge_context
{
	t_operation	a;
	t_operation	b;
	t_list		**dst;
	t_list		**current;
}				t_merge_context;

typedef struct s_bubble_context
{
	t_list		*out;
	int			i;
	int			n;
	int			max_gap;
	bool		*changed;
	bool		is_a;
}				t_bubble_context;

typedef struct s_cancel_context
{
	t_operation		op;
	t_list			*current;
	t_list			**dst;
	bool			*has_changed;
	t_list			**current_ptr;
}					t_cancel_context;

typedef struct s_optimizer_config
{
	int		max_bubble_gap;
	bool	enable_merge_neighbors;
	bool	enable_cancel_pairs;
	bool	enable_cancel_across;
	int		max_iterations;
}					t_optimizer_config;

typedef struct s_optimization_strategy
{
	char			*name;
	bool			(*can_apply)(t_list *seq);
	t_list*			(*apply)(t_list *seq, t_optimizer_arena *arena, bool *changed);
	int				priority;
}					t_optimization_strategy;

t_optimizer_arena	*create_optimizer_arena(size_t capacity);
void				destroy_optimizer_arena(t_optimizer_arena *arena);
t_optimizer_arena	*initialize_cancel_arena(t_list *src, bool *changed);

t_optimizer_config	*create_default_optimizer_config(void);
t_optimizer_config	*create_custom_optimizer_config(int max_gap, bool enable_merge, bool enable_cancel_pairs, bool enable_cancel_across, int max_iterations);
void				free_optimizer_config(t_optimizer_config *config);

t_optimization_strategy	*create_bubble_strategy(void);
t_optimization_strategy	*create_merge_strategy(void);
t_optimization_strategy	*create_cancel_strategy(void);
t_optimization_strategy	**get_optimization_strategies(int *count);
void				free_strategy_registry(void);

void				*copy_operation(void *content);
void				add_operation_to_list(t_list **dst, t_operation op);
bool				validate_operation_sequence(t_list *seq);
void				replace_sequence_if_changed(t_list **seq, t_list *new_seq, bool changed, bool *overall_changed);
t_operation	get_operation_at_index(t_list *list, int index);
void		optimize_ops(t_list **seq);
void		apply_optimization_pass(t_list **seq, bool *changed);
void		run_optimization_loop(t_list **seq);

t_list		*bubble_across_other_stack(t_list *src, int max_gap, bool *changed);
bool		is_pure_a(t_operation op);
bool		is_pure_b(t_operation op);

t_list		*merge_neighbors(t_list *src, bool *changed);
t_operation	get_absorption_result_rr_rra(t_operation a);
t_operation	get_absorption_result_rr_rrb(t_operation a);
t_operation	get_absorption_result_rrr_ra(t_operation a);
t_operation	get_absorption_result_rrr_rb(t_operation a);
bool		try_merge_operations(t_merge_context *ctx);
bool		try_merge_rotate_pairs(t_merge_context *ctx);
bool		try_merge_swap_pairs(t_merge_context *ctx);
bool		try_merge_absorption_cases(t_merge_context *ctx);

t_list		*cancel_inverse_pairs(t_list *src, bool *changed);
bool		is_inverse(t_operation a, t_operation b);
t_list		*cancel_across_other_stack_a(t_list *src, bool *changed);
t_list		*cancel_across_other_stack_b(t_list *src, bool *changed);
t_operation	get_inverse_a_operation(t_operation op);
t_operation	get_inverse_b_operation(t_operation op);
void		copy_operations_to_list(t_list **dst, t_list *src_start, t_list *src_end);
bool		search_for_inverse_a(t_operation op, t_list *current, t_list **dst, bool *has_changed);
bool		search_for_inverse_b(t_operation op, t_list *current, t_list **dst, bool *has_changed);
void		process_operation_a(t_cancel_context *ctx);
void		process_operation_b(t_cancel_context *ctx);
void		process_inverse_cancellation(t_list *src, t_list **dst, bool *has_changed);

bool		touches_a(t_operation op);
bool		touches_b(t_operation op);
bool		is_barrier(t_operation op);

void		list_swap_nodes(t_list *list, int i, int j);
t_list		*list_remove_at(t_list *list, int index);
t_list		*list_insert_at(t_list *list, t_operation op, int index);
t_operation	get_operation_at_index(t_list *list, int index);
void		set_operation_at_index(t_list *list, int index, t_operation op);
bool		bubble_operation(t_list *out, int i, int j, bool is_a);
void		process_operation_at_index(t_bubble_context *ctx);
bool		search_and_bubble_a(t_bubble_context *ctx);
bool		search_and_bubble_b(t_bubble_context *ctx);
t_operation	get_target_operation_for_a(t_operation a);
t_operation	get_target_operation_for_b(t_operation a);

#endif



typedef struct s_node
{
	int			content;
	struct s_node		*next;
	struct s_node		*prev;
}				t_node;


typedef struct s_stack
{
    t_node		*head;
    t_node		*tail;
    int			size;
}				t_stack;

t_stack *create_stack(void);
int get_size(t_stack *stack);
void push_to_stack(t_stack *stack, t_node *node);
t_node *pop(t_stack **stack);
t_node *create_node(int content);
void clear_stack(t_stack *stack);
void fill_stack(t_stack *stack, int *numbers, int n);
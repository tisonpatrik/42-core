
#include "../../include/optimizer.h"

#define MAX_STRATEGIES 10

typedef struct s_strategy_registry
{
	t_optimization_strategy	*strategies[MAX_STRATEGIES];
	int						count;
}						t_strategy_registry;

static t_strategy_registry	*g_registry = NULL;

static void	initialize_strategy_registry(void)
{
	if (g_registry)
		return;
	g_registry = malloc(sizeof(t_strategy_registry));
	if (!g_registry)
		return;
	g_registry->count = 0;
	g_registry->strategies[g_registry->count++] = create_bubble_strategy();
	g_registry->strategies[g_registry->count++] = create_merge_strategy();
	g_registry->strategies[g_registry->count++] = create_cancel_strategy();
}

static void	sort_strategies_by_priority(t_optimization_strategy **strategies, int count)
{
	int						i;
	int						j;
	t_optimization_strategy	*temp;

	i = 0;
	while (i < count - 1)
	{
		j = 0;
		while (j < count - i - 1)
		{
			if (strategies[j]->priority > strategies[j + 1]->priority)
			{
				temp = strategies[j];
				strategies[j] = strategies[j + 1];
				strategies[j + 1] = temp;
			}
			j++;
		}
		i++;
	}
}

t_optimization_strategy	**get_optimization_strategies(int *count)
{
	if (!g_registry)
		initialize_strategy_registry();
	if (!g_registry)
	{
		*count = 0;
		return (NULL);
	}
	sort_strategies_by_priority(g_registry->strategies, g_registry->count);
	*count = g_registry->count;
	return (g_registry->strategies);
}

void	free_strategy_registry(void)
{
	if (g_registry)
	{
		free(g_registry);
		g_registry = NULL;
	}
}

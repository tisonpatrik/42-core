#include "models.h"

void	init_data(t_ps *data, int argc, char *argv[], bool writing_mode);
void	sort(t_ps *data);
void	print_operations(t_list *op_list);
void	free_data(t_ps *data);

int	main(int argc, char *argv[])
{
	t_ps	data;

	init_data(&data, argc, argv, true);
	sort(&data);
	print_operations(data.op_list);
	free_data(&data);
	exit(EXIT_SUCCESS);
}
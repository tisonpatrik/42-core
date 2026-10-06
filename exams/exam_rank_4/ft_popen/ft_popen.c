#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

int	ft_popen(const char *file, char *const argv[], char type)
{
	int		fds[2];
	int		child_end;
	pid_t	pid;

	if (!file || !*file || !argv || !argv[0]
		|| (type != 'r' && type != 'w'))
		return (-1);
	if (pipe(fds) == -1)
		return (-1);
	pid = fork();
	if (pid == -1)
	{
		close(fds[0]);
		close(fds[1]);
		return (-1);
	}
	child_end = (type == 'r');
	if (pid == 0)
	{
		close(fds[1 - child_end]);
		if (dup2(fds[child_end], child_end) == -1)
		{
			close(fds[child_end]);
			exit(1);
		}
		if (fds[child_end] != child_end)
			close(fds[child_end]);
		execvp(file, argv);
		exit(1);
	}
	close(fds[child_end]);
	return (fds[1 - child_end]);
}

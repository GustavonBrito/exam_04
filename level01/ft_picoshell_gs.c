#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

static void	close_fd(int fd[2])
{
	close(fd[1]);
	close(fd[0]);
}

void	picoshell(int **cmds[])
{
	int		status = 1;
	pid_t	pid;
	int		prev_fd = -1;
	int		children = 0;
	int		error_code = 0;
	int		i;
	int 	fd[2];

	if (!cmds || !cmds[0])
		return (1);
	
	while (cmds[i])
	{
		if (cmds[i + 1])
			if (pipe(fd) == -1)
				return 1;
		else
		{
			fd[0] = -1;
			fd[1] = -1;
		}

		pid = fork();
		if (pid == -1)
		{
			if (cmds[i + 1])
				close_fd(fd);
			return 1;
		}

		if (pid == 0)
		{

		}
	}
}
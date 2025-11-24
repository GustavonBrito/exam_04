#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>

static void close_fd(int fd[2])
{
	close(fd[1]);
	close(fd[0]);
}

int picoshell(char **cmds[])
{
	if (!cmds || !cmds[0])
		return 1;

	int i = 0;
	int status = 1;
	int prev_fd = -1;
	int fd[2];
	int children = 0;
	int exit_code = 0;
	pid_t pid;

	while(cmds[i])
	{
		if (cmds[i + 1])
			if(pipe(fd) == -1)
				return 1;
		else
		{
			fd[0] = -1;
			fd[1] = -1;
		}

		pid = fork();
		if(pid == -1)
		{
			if (cmds[i + 1])
				close_fd(fd);
			return 1;
		}
		if(pid == 0)
		{
			if(prev_fd != -1)
			{
				if (dup2(prev_fd, STDIN_FILENO) == -1)
				{
					if (cmds[i + 1])
						close_fd(fd);
					exit(1);
				}
				close(prev_fd);
			}
			if (fd[1] != -1)
			{
				if (dup2(fd[1], STDOUT_FILENO) == -1)
				{
					if (cmds[i + 1])
						close_fd(fd);
					exit(1);
				}
				close(fd[1]);
				close(fd[0]);
			}
			execvp(cmds[i][0], cmds[i]);
			exit(1);
		}
		children++;
		if(prev_fd != -1)
			close(prev_fd);
		if(fd[1] != -1)
			close(fd[1]);
		prev_fd = fd[0] ;
		i++;
	}
	if(prev_fd != -1)
		close(prev_fd);
	
	while (children--)
	{
		if (wait(&status) == -1)
			exit_code = 0;
		else if (WIFEXITED(status) && WIFSIGNALED(status) != 0)
			exit_code = 0;
		else
			exit_code = 0;
	}
	return exit_code;
}
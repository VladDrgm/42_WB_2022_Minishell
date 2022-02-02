#include "../incl/pipex.h"
# include <limits.h>
# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include <fcntl.h>
# include <errno.h>
# include <sys/wait.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
#include <sys/types.h>
#include <unistd.h>
#include <signal.h>


void	ft_initialize_fds(int *fd_temp)
{

	dup2(STDIN_FILENO, fd_temp[0]);
	dup2(STDOUT_FILENO, fd_temp[1]);
}

void parent(int *fd, pid_t pid)
{
	char c;

	waitpid(pid, NULL, 0);
	close(fd[1]);
	while(read(fd[0], &c, 1))
		write(1, &c, 1);
	close(fd[0]);
}

void heredoc(char *stop_word, int fd_stream[2], int fd_out)
{
	char *out;
	dup2(fd_stream[0], STDIN_FILENO);
	dup2(fd_stream[1], STDOUT_FILENO);
	while(1)
	{
		out = readline("<HEREDOC> ");
		if (out == NULL)
			break;
		if (!strcmp(out, stop_word)) // change to ft fuinction
		{
			free (out);
			break;
		}
		write(fd_out, out, strlen(out));
		write(fd_out, "\n", 1);
		//write(2, out, ft_strlen(out));
		//write(2, "\n", 1);
		free(out);
	}
	close(fd_out);
	close(fd_stream[0]);
	close(fd_stream[1]);
	close(STDIN_FILENO);
	close(STDOUT_FILENO);
	exit(0) ;
}

void child(int* fd, int *fd_stream)
{
	close(fd[0]);
	heredoc("stop", fd_stream, fd[1]);
	exit(0);
}
int main(void)
{
	int fd[2];
	int fd_stream[2];

	ft_initialize_fds(fd_stream);
	pipe(fd);
	pid_t pid = fork();
	if (!pid)
		child(fd, fd_stream);
	else
		parent(fd, pid);
}
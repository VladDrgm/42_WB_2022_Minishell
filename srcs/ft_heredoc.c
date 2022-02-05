#include "../incl/minishell.h"

void heredoc_parent(int *fd, pid_t pid)
{
	waitpid(pid, NULL, 0);
	close(fd[1]);
}

void heredoc(char *stop_word, int fd_stream[2], int fd_out, char *keyword)
{
	char *out;

	dup2(fd_stream[0], STDIN_FILENO);
	dup2(fd_stream[1], STDOUT_FILENO);
	while(1)
	{
		out = readline(keyword);
		if (out == NULL)
			break;
		if (stop_word != NULL)
		{
			if (!strcmp(out, stop_word)) // change to ft fuinction
			{
				free(out);
				break;
			}
		}
		if(write(fd_out, out, ft_strlen(out)) == -1)
		{
			free (out);
			break;
		}
		if(write(fd_out, "\n", 1) == -1)
		{
			free (out);
			break;
		}
		free(out);
	}
	close(fd_out);
	close(fd_stream[0]);
	close(fd_stream[1]);
	close(STDIN_FILENO);
	close(STDOUT_FILENO);
}

void handle_sigterm_heardoc(int signum)
{
	if (signum == SIGUSR1)
	{
		close(STDIN_FILENO);
		close(STDOUT_FILENO);
	}
}

void heredoc_child(int* fd, int *fd_stream, char *stop_name, char *keyword)
{
	signal(SIGUSR1, handle_sigterm_heardoc);
	close(fd[0]);
	heredoc(stop_name, fd_stream, fd[1], keyword);
	exit(0);
}
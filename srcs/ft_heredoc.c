#include "../incl/minishell.h"

void heredoc_parent(int *fd, pid_t pid)
{
	waitpid(pid, NULL, 0);
	close(fd[1]);
}

void heredoc(char *stop_word, int fd_stream[2], int fd_out, char *keyword)
{
	char *out;
	int flag = 0;

	dup2(fd_stream[0], STDIN_FILENO);
	dup2(fd_stream[1], STDOUT_FILENO);
	while(1)
	{
		out = readline(keyword);
		if (out == NULL)
		{
			break;
		}
		if (stop_word != NULL)
		{
			if (!strcmp(out, stop_word)) // change to ft fuinction
			{
				free(out);
				flag = 1;
				break;
			}
		}
		if(write(fd_out, out, ft_strlen(out)) == -1)
		{
			free (out);
			flag = 1;
			break;
		}
		if(write(fd_out, "\n", 1) == -1)
		{
			free (out);
			flag = 1;
			break;
		}
		free(out);
	}
	if(!flag)
		write(1, "\n", 1);
	close(fd_out);
	close(fd_stream[0]);
	close(fd_stream[1]);
	close(STDIN_FILENO);
	close(STDOUT_FILENO);
	close(STDERR_FILENO);
}

void handle_sigterm_heardoc(int signum)
{
	if (signum == SIGINT)
	{
		write(1, "\n", 1);
		close(STDIN_FILENO);
		close(STDOUT_FILENO);
		close(STDERR_FILENO);
	}
}

void heredoc_child(int* fd, int *fd_stream, char *stop_name, char *keyword)
{
	signal(SIGINT, handle_sigterm_heardoc);
	close(fd[0]);
	heredoc(stop_name, fd_stream, fd[1], keyword);
	free_global();
}

void	ft_free_heredoc_fds(int **fd_docks)
{
	int	i;
	int	last_index;

	if (fd_docks == NULL)
		return ;
	i = 0;
	last_index = ((t_command *)ft_lstlast(g_access.parser2exec)->content)->index;
	while( i <= last_index)
	{
		if(fd_docks[i] != NULL)
		{
			close(fd_docks[i][0]);
			free(fd_docks[i]);
		}
		i++;
	}
	if (fd_docks != NULL)
		free(fd_docks);
}

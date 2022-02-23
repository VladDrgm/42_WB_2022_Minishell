#include "../incl/minishell.h"

void	ft_free_split(char **split)
{
	int	i;

	i = 0;
	while (split[i] != NULL)
	{
		free(split[i]);
		i++;
	}
	free(split);
}


void	ft_pipex_error_handler_child(char *error_msg, int **fd_docks, int fd_stream[2], pid_t *pidt)
{
	ft_smart_free((void **)&pidt);
	ft_free_heredoc_fds(fd_docks);
	if (fd_stream != NULL)
	{
		close(fd_stream[0]);
		close(fd_stream[1]);

	}
	perror(error_msg);
	free_global();
	close(STDIN_FILENO);
	close(STDOUT_FILENO);
	close(STDERR_FILENO);
	exit(EXIT_FAILURE);
}

void	ft_pipex_error_handler_parent(char *error_msg, int **fd_docks, int fd_stream[2], pid_t *pidt)
{

	ft_smart_free((void **)&pidt);
	ft_free_heredoc_fds(fd_docks);
	if (fd_stream != NULL)
	{
		close(fd_stream[0]);
		close(fd_stream[1]);
		
	}
	perror(error_msg);
	free_global();
	exit(EXIT_FAILURE);
}

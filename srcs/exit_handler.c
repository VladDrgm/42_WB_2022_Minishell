#include "../incl/minishell.h"

/**
	@brief Error handler that closes file desriptors and frees allocated
	memory in case of error in child process. Afterwards exits the programm.
	(ft_pipex_error_handler_child)
	@param error_msg Error message to be printed.
	@param fd_docks File descriptors from heredocs.
	@param fd_stream File descprictors for terminal streams.
	@param pidt Array of created pids of forked child processes
		that need to be closed in case of pipe failure.
	@return None.
	@exception inherited system filedesriptors from parent need to be closed.
*/
void	ft_err_ch(char *error_msg, int **fd_docks, int fd_stream[2], pid_t *pidt)
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

/**
	@brief Error handler that closes file desriptors and frees allocated
	memory in case of error in parent process. Afterwards exits the programm.
	(ft_pipex_error_handler_parent)
	@param error_msg Error message to be printed.
	@param fd_docks File descriptors from heredocs.
	@param fd_stream File descprictors for terminal streams.
	@param pidt Array of created pids of forked child processes
		that need to be closed in case of pipe failure.
	@return None.
*/
void	ft_err_par(char *error_msg, int **fd_docks, int fd_stream[2], pid_t *pidt)
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

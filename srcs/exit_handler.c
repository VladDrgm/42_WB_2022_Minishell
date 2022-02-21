#include "../incl/minishell.h"

void	ft_close_fd(void)
{
	close(STDIN_FILENO);
	close(STDOUT_FILENO);
	close(STDERR_FILENO);
}

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


void	ft_exit_on_error2(char *error_msg)
{
	perror(error_msg);
	ft_close_fd();
	exit(EXIT_FAILURE);
}

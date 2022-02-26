/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_heredoc_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamuller <mamuller@student.42wolfsburg>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/25 15:23:33 by mamuller          #+#    #+#             */
/*   Updated: 2022/02/25 15:23:33 by mamuller         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/minishell.h"

/**
	@brief Frees heredoc filedesriptors and global variables and 
		afterwards exits the heredoc child process.
	@param fd_docks Pointer to file descriptors from heredocs.
	@return None.
*/
void	ft_heredoc_child_free(int **fd_docks)
{
	ft_free_heredoc_fds(fd_docks);
	free_global();
	exit (0);
}

/**
	@brief Handles signals for heredocs and closes standard
		file descriptors of the system.
	@param signum Signal number.
	@return None.
*/
void	ft_handle_sigterm_heredoc(int signum)
{
	if (signum == SIGINT)
	{
		write(1, "\n", 1);
		close(STDIN_FILENO);
		close(STDOUT_FILENO);
		close(STDERR_FILENO);
	}
}

/**
	@brief Closes and frees all heredoc filedescriptors if they are
		existent.
	@param fd_docks Pointer to file descriptors from heredocs.
	@return None.
*/
void	ft_free_heredoc_fds(int **fd_docks)
{
	int	i;
	int	last_index;

	if (fd_docks == NULL)
		return ;
	i = 0;
	last_index = \
		((t_command *)ft_lstlast(g_access.parser2exec)->content)->index;
	while (i <= last_index)
	{
		if (fd_docks[i] != NULL)
		{
			close(fd_docks[i][0]);
			free(fd_docks[i]);
		}
		i++;
	}
	if (fd_docks != NULL)
		free(fd_docks);
}

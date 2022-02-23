/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_heredoc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamuller <mamuller@student.42wolfsburg>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/24 21:03:19 by mamuller          #+#    #+#             */
/*   Updated: 2022/02/24 21:03:19 by mamuller         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/minishell.h"

/**
	@brief Parent process of heredoc that waits for child process to finish. 
	@param fd Pointer to file descriptor.
	@param pid Process Id.
	@return None.
*/
void	heredoc_parent(int *fd, pid_t pid)
{
	waitpid(pid, NULL, 0);
	close(fd[1]);
}

/**
	@brief Checks if the entered line matches the stop_word.
		If not, the line and a new line are writen into fd_out,
		else the flag for stopping heredoc is sent and the loop
		ends.
	@param out String of user input in terminal.
	@param stop_word String passed by user to end the heredoc
		terminal input.
	@param flag Pointer to flag for terminating the reading
		of terminal input.
	@param fd_out File descriptor number for output.
	@return 1 on termination else 0.
	@exception Ctrl-D stops the heredoc.
*/
static int	ft_heredoc_input_sw_check(char *out, char *stop_word, \
	int *flag, int fd_out)
{
	if (out == NULL)
		return (1);
	if (stop_word != NULL)
	{
		if (!ft_strcmp(out, stop_word))
		{
			ft_smart_free((void **)&out);
			*flag = 1;
			return (1);
		}
	}
	if (write(fd_out, out, ft_strlen(out)) == -1)
	{
		ft_smart_free((void **)&out);
		*flag = 1;
		return (1);
	}
	if (write(fd_out, "\n", 1) == -1)
	{
		ft_smart_free((void **)&out);
		*flag = 1;
		return (1);
	}
	return (0);
}

/**
	@brief Connects file descriptors to terminal streams and writes 
		terminal inputdata into output file descriptor. Also closes
		all necessary file descriptors.
	@param stop_word String passed by user to end the heredoc
		terminal input.
	@param fd_stream File descprictors for terminal streams.
	@param fd_out File descriptor number for output.
	@param keyword Pointer to char/string to be shown on terminal after
		readline call.
	@return None.
*/
void	heredoc(char *stop_word, int fd_stream[2], int fd_out, char *keyword)
{
	char	*out;
	int		flag;

	flag = 0;
	dup2(fd_stream[0], STDIN_FILENO);
	dup2(fd_stream[1], STDOUT_FILENO);
	while (1)
	{
		out = readline(keyword);
		if (ft_heredoc_input_sw_check(out, stop_word, &flag, fd_out))
			break ;
		free(out);
	}
	if (!flag)
		write(1, "\n", 1);
	close(fd_out);
	close(fd_stream[0]);
	close(fd_stream[1]);
	close(STDIN_FILENO);
	close(STDOUT_FILENO);
	close(STDERR_FILENO);
}

/**
	@brief Handles signals for heredocs and closes standard
		file descriptors of the system.
	@param signum Signal number.
	@return None.
*/
void	handle_sigterm_heredoc(int signum)
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
	@brief Heredoc child process that inititates signal handling,
		closes unused file descriptor and call main part of heredoc
		execution.
	@param fd File descriptor for redirect stdin and stdout
		between children.
	@param fd_stream File descprictors for terminal streams.
	@param stop_word String passed by user to end the heredoc
		terminal input.
	@param keyword Pointer to char/string to be shown on terminal after
		readline call.
	@return None.
*/
void	ft_hd_ch(int *fd, int *fd_stream, char *stop_word, char *keyword)
{
	signal(SIGINT, handle_sigterm_heredoc);
	close(fd[0]);
	heredoc(stop_word, fd_stream, fd[1], keyword);
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

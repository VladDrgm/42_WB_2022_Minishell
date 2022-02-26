/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipex_error_handling.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamuller <mamuller@student.42wolfsburg>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/25 16:04:49 by mamuller          #+#    #+#             */
/*   Updated: 2022/02/25 16:04:49 by mamuller         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
void	ft_err_ch(char *error_msg, int **fd_docks, int fd_stream[2], \
	pid_t *pidt)
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
void	ft_err_par(char *error_msg, int **fd_docks, int fd_stream[2], \
	pid_t *pidt)
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

/**
	@brief Calls the error function of the child process with respective
		error message (ft_pipex_child_error_flag_handler).
	@param error_flag Error flag that indicates the type of occured
		error.
	@param fd_docks File descriptors from heredocs.
	@param fd_stream File descprictors for terminal streams.
	@param pidt Array of created pids of forked child processes.
	@return None.
*/
void	ft_ch_err_fl(int error_flag, int **fd_docks, \
	int *fd_stream, pid_t *pidt)
{
	if (error_flag == 1)
		ft_err_ch(FT_ERROR_PIPEX_FD_DUP_FAIL, fd_docks, fd_stream, pidt);
	else if (error_flag == 2)
		ft_err_ch(FT_ERROR_PIPEX_OUTFILE_FAIL, fd_docks, fd_stream, pidt);
	else if (error_flag == 3)
		ft_err_ch(FT_ERROR_PIPEX_INFILE_FAIL, fd_docks, fd_stream, pidt);
}

/**
	@brief Closes file desriptor in regards to given error_flag.
	@param error_flag Error flag that indicates which file desriptor
		has to be closed (2 for outfile error, 3 on infile error).
	@param fd File descriptor structure for redirect stdin and stdout
		between children.
	@return Returns passed error_flag.
*/
int	ft_fc_error_exit(int error_flag, t_fd fd)
{
	if (error_flag != 0)
	{
		if (error_flag == 2)
			close(fd.in[0]);
		else if (error_flag == 3)
			close(fd.out[1]);
		return (error_flag);
	}
	return (error_flag);
}

/**
	@brief In case of errorin child process the in and out file
		descriptors are closed.
	@param error_flag Inidcates of an error occured.
	@param fd File descriptor structure for redirect stdin and stdout
		between children.
	@return None.
*/
void	ft_pipex_child_in_out_error(int error_flag, t_fd fd)
{
	if (error_flag == 1)
	{
		close(fd.in[0]);
		close(fd.in[1]);
		close(fd.out[0]);
		close(fd.out[1]);
	}
}

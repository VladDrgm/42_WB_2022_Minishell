/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamuller <mamuller@student.42wolfsburg>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/24 16:16:43 by mamuller          #+#    #+#             */
/*   Updated: 2022/02/24 16:16:43 by mamuller         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/minishell.h"

/**
	@brief Connects stdin and stdout of the child to the correct pipe
		end (could be child or parent). This is where the magic happens!
	@param fd File descriptor structure for redirect stdin and stdout
		between children.
	@param fd_stream File descprictors for terminal streams.
	@param i Index for child pids.
	@return Returns 1 on error else 0.
	@exception The first data stream for input is from terminal input.
	@exception The last created child directs the output to the terminal.
*/
static int	ft_pipex_child_in_out_init(t_fd fd, int fd_stream[2], int i)
{
	int	error_flag;
	int	last_ind;

	error_flag = 0;
	last_ind = ((t_command *)ft_lstlast(g_access.parser2exec)->content)->index;
	close(fd.out[0]);
	if (i == 0)
		if (dup2(fd_stream[0], fd.in[0]) == -1)
			error_flag = 1;
	if (i == last_ind)
		if (dup2(fd_stream[1], fd.out[1]) == -1)
			error_flag = 1;
	if (dup2(fd.in[0], STDIN_FILENO) == -1)
		error_flag = 1;
	if (dup2(fd.out[1], STDOUT_FILENO) == -1)
		error_flag = 1;
	ft_pipex_child_in_out_error(error_flag, fd);
	if (i == 0)
		close(fd.in[1]);
	return (error_flag);
}

/**
	@brief Makes fork in the parent process to run cmd in child
		process and on error initiates closing and freeing of already
		allocated/assigned ressources.
	@param pidt Array of created pids of forked child processes
		that need to be closed in case of fork failure.
	@param fd_docks File descriptors from heredocs that need to be
		closed in case of fork failure.
	@param fd_stream File descprictors for terminal streams that need to
		be closed in case of fork failure.
	@param i Index for child pids.
	@return None.
*/
static void	ft_pipex_fork_inititaor(pid_t *pidt, int **fd_docks, \
	int *fd_stream, int i)
{
	pidt[i] = fork();
	if (pidt[i] == -1)
		ft_err_par(FT_ERROR_PIPEX_FORK_FAIL, fd_docks, fd_stream, pidt);
}

/**
	@brief Inititates pipe(s) in the parent process for usage in child
		and on error initiates closing and freeing of already
		allocated/assigned ressources.
	@param pidt Array of created pids of forked child processes
		that need to be closed in case of pipe failure.
	@param fd_docks File descriptors from heredocs that need to be
		closed in case of pipe failure.
	@param fd_stream File descprictors for terminal streams that need to
		be closed in case of pipe failure.
	@param fd File descriptor structure for redirect stdin and stdout
		between children.
	@return None.
*/
static void	ft_pipex_pipe_initiator(pid_t *pidt, int **fd_docks, \
	int *fd_stream, t_fd *fd)
{
	if (pipe((*fd).out) == -1)
		ft_err_par(FT_ERROR_PIPEX_PIPE_FAIL, fd_docks, fd_stream, pidt);
}

/**
	@brief Creates pipes and respective system ressources for every
		command that has to be executed and manages the correct
		redirection of ipput and output.
	@param fd_s File descprictors for terminal streams.
	@param envp System environmental variables to be passed to
		execution function for non-builtins as array of strings.
	@param fd_d File descriptors from heredocs.
	@param pidt Array for pids of forked child processes.
	@return None.
*/
void	ft_pipex(int fd_s[2], char **envp, int **fd_d, pid_t *pidt)
{
	int		i;
	t_fd	fd;
	t_list	*cmd_list;

	i = 0;
	cmd_list = g_access.parser2exec;
	ft_pipex_pipe_initiator(pidt, fd_d, fd_s, &fd);
	fd.in[1] = fd.out[1];
	while (cmd_list != NULL)
	{
		fd.in[0] = fd.out[0];
		ft_pipex_pipe_initiator(pidt, fd_d, fd_s, &fd);
		ft_pipex_fork_inititaor(pidt, fd_d, fd_s, i);
		if (pidt[i] == 0)
		{
			if (ft_pipex_child_in_out_init(fd, fd_s, i))
				ft_err_ch(FT_ERROR_PIPEX_FD_DUP_FAIL, fd_d, fd_s, pidt);
			ft_ch_err_fl(ft_fc(&cmd_list, i, fd, fd_d[i]), fd_d, fd_s, pidt);
			ft_free_heredoc_fds(fd_d);
			ft_pipex_clean_child_exec(cmd_list, envp, pidt, i);
		}
		else
			ft_pipex_parent_exec(&cmd_list, fd, i, pidt);
		ft_pipex_iterator(&i, &cmd_list);
	}
}

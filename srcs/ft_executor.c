/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_executor.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamuller <mamuller@student.42wolfsburg>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/25 15:13:16 by mamuller          #+#    #+#             */
/*   Updated: 2022/02/25 15:13:16 by mamuller         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/minishell.h"

/**
	@brief Waits for children to exit and sets their exit value into global
		variable. Frees heredoc file descriptor and array with child pids.
	@param last_index Index of the last element in the list of command.
	@param fd_docks File descriptors from heredocs.
	@param pidt Pointer to array of created pids of forked child processes.
	@return None.
*/
static void	ft_pipex_parent_free(int last_index, int **fd_docks, pid_t *pidt)
{
	int	x;
	int	status;

	x = 0;
	while (x <= last_index)
	{
		waitpid(pidt[x], &status, 0);
		ft_smart_free((void **)&(g_access.last_return));
		g_access.last_return = ft_itoa(WEXITSTATUS(status));
		x++;
	}
	ft_free_heredoc_fds(fd_docks);
	ft_smart_free((void **)&pidt);
}

/**
	@brief In case of heredoc type (<<) reads data from terminal into a
		pipe in child process and waits for that process.
	@param cmd_list Array of strings with commands and their
		respective flags and arguments.
	@param last_index Index of the last element in the list of command.
	@param fd_s File descprictors for terminal streams.
	@return Return list of created heredoc file desriptors.
*/
static int	**ft_heredoc_init(t_list *cmd_list, int last_index, int fd_s[2])
{
	int			**fd_docks;
	pid_t		pid;
	t_command	*cmd;

	fd_docks = ft_calloc(last_index + 1, sizeof(int *));
	while (cmd_list != NULL)
	{
		cmd = (t_command *)cmd_list->content;
		if (!ft_strcmp(cmd->comm_table[0], "<<") && \
			cmd->cmd_type == FT_CMD_TYPE_REDIRECT)
		{
			ft_heredoc_pipe_init(fd_docks, fd_s, cmd->index);
			pid = fork();
			if (!pid)
			{
				ft_hd_ch(fd_docks[cmd->index], fd_s, cmd->comm_table[1], "> ");
				ft_heredoc_child_free(fd_docks);
			}
			else
				ft_heredoc_parent(fd_docks[cmd->index], pid);
		}
		cmd_list = cmd_list->next;
	}
	return (fd_docks);
}

/**
	@brief Prepares system ressources for executions like initialization of
		the stream file descriptor with terminal stdin and stdout.
		Executes the commands in regards of their types and cleans
		system afterwards.
	@param envp System environmental variables to be passed to 
		execution function for non-builtins as array of strings.
	@return None.
*/
void	ft_executor(char **envp)
{
	int		fd_stream[2];
	pid_t	*pidt;
	int		**fd_docks;
	int		last_ind;

	fd_stream[0] = 0;
	fd_stream[1] = 0;
	if (dup2(STDIN_FILENO, fd_stream[0]))
		ft_err_par(FT_ERROR_PIPEX_FD_DUP_FAIL, NULL, NULL, NULL);
	if (dup2(STDOUT_FILENO, fd_stream[1]))
		ft_err_par(FT_ERROR_PIPEX_FD_DUP_FAIL, NULL, NULL, NULL);
	last_ind = ((t_command *)ft_lstlast(g_access.parser2exec)->content)->index;
	fd_docks = ft_heredoc_init(g_access.parser2exec, last_ind, fd_stream);
	pidt = ft_calloc(last_ind + 1, sizeof(int *));
	ft_pipex(fd_stream, envp, fd_docks, pidt);
	ft_pipex_parent_free(last_ind, fd_docks, pidt);
	ft_free_linked_list(&g_access.parser2exec, FT_LIST_TYPE_COMMAND, 1);
	return ;
}

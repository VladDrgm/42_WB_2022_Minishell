/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipex_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamuller <mamuller@student.42wolfsburg>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/25 15:21:44 by mamuller          #+#    #+#             */
/*   Updated: 2022/02/25 15:21:44 by mamuller         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/minishell.h"

/**
	@brief Increments the necessary values for looping through 
		the commands in cmd_list.
	@param i Pointer to index for child pids.
	@param cmd_list Array of strings with commands and their
		respective flags and arguments.
	@return None.
*/
void	ft_pipex_iterator(int *i, t_list **cmd_list)
{
	(*i)++;
	if (*cmd_list)
		*cmd_list = (*cmd_list)->next;
}

/**
	@brief Calls system function for executing commands if
		command type indicates this. Otherwise in case of builtin cmd
		the function for builtin fct redirection is called.
	@param cmd_list Array of strings with commands and their
		respective flags and arguments.
	@param envp System environmental variables to be passed to 
		execution function for non-builtins as array of strings.
	@param pid Process ID that indicates that this is a child process.
	@return None.
	@exception If system function execve fails, file desriptors and
		memory are cleaned.
*/
static void	ft_pipex_execute_child(t_list *cmd_list, char **envp, pid_t pid)
{
	t_command	*cmd;

	if (cmd_list != NULL)
		cmd = (t_command *)(cmd_list->content);
	else
		return ;
	if (cmd->cmd_type == FT_CMD_TYPE_SYSTEM)
		if (execve(cmd->path, cmd->comm_table, envp) == -1)
			ft_err_ch(FT_ERROR_PIPEX_EXEC_FAIL, NULL, NULL, NULL);
	if (cmd->cmd_type == FT_CMD_TYPE_BUILT_IN)
	{
		ft_execve(cmd->comm_table, pid);
	}
}

/**
	@brief Calls the cmd executing function in the child process 
		and cleans the system ressources afterwards.
	@param cmd_list Array of strings with commands and their
		respective flags and arguments.
	@param envp System environmental variables to be passed to 
		execution function for non-builtins as array of strings.
	@param pidt Pointer to array for pids of forked child processes.
	@param i Pointer to index for child pids.
	@return None.
*/
void	ft_pipex_clean_child_exec(t_list *cmd_list, \
	char **envp, pid_t *pidt, int i)
{
	int	exit_value;
	int	current_pidt;

	current_pidt = pidt[i];
	ft_smart_free((void **)&pidt);
	ft_pipex_execute_child(cmd_list, envp, current_pidt);
	exit_value = ft_atoi(g_access.last_return);
	free_global();
	close(STDERR_FILENO);
	close(STDIN_FILENO);
	close(STDOUT_FILENO);
	exit(exit_value);
}

/**
	@brief Loops through the command list until the next indes is found
		and in case of buildins calls their execution fct.
	@param cmd_list Array of strings with commands and their
		respective flags and arguments.
	@param fd File descriptor structure for redirect stdin and stdout
		between children.
	@param i Pointer to index for child pids.
	@param pidt Array of created pids of forked child processes.
	@return None.
	@exception in case of first or last command the in and out file
		desriptors are closed accordingly.
*/
void	ft_pipex_parent_exec(t_list **cmd_list, t_fd fd, int i, int *pidt)
{
	int			last_ind;
	t_command	*cmd;

	last_ind = ((t_command *)ft_lstlast(g_access.parser2exec)->content)->index;
	if (i == 0)
		close(fd.in[1]);
	while (*cmd_list != NULL)
	{
		cmd = (t_command *)(*cmd_list)->content;
		if (cmd->cmd_type != FT_CMD_TYPE_REDIRECT)
			break ;
		*cmd_list = (*cmd_list)->next;
	}
	close(fd.in[0]);
	close(fd.out[1]);
	if (i == last_ind)
		close(fd.out[0]);
	if (cmd->cmd_type == FT_CMD_TYPE_BUILT_IN)
		ft_execve(cmd->comm_table, pidt[i]);
}

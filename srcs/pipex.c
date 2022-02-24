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
	@brief Checks the filetype (output) and opens file with necessar
		 permissions to respective file descriptor.
	@param filename Filename of output file.
	@param type Indicator for output file.
	@param err_fl Pointer to error flag.
	@param fd Pointer to file descriptor value for redirect stdin and stdout
		between children.
	@return 2 on error else 0.
	@exception If file is not existent it will be created.
*/
int	out_redirect(char *filename, int type, int *fd)
{
	int	permissions;

	permissions = 0;
	if (type == OUT_WRITE)
		permissions = O_WRONLY | O_CREAT | O_TRUNC;
	else if (type == OUT_APPEND)
		permissions = O_WRONLY | O_APPEND | O_CREAT;
	*fd = open(filename, permissions, 0777);
	if (*fd == -1)
		return (2);
	return (0);
}

/**
	@brief Checks the filetype (input) and opens file to respective fil
		 descriptor.
	@param filename Filename of input file.
	@param type Indicator for input file.
	@param err_fl Pointer to error flag.
	@param fd Pointer to file descriptor value for redirect stdin and stdout
		between children.
	@return 3 on error else 0.
*/
int	in_redirect(char *filename, int type, int *fd)
{
	int	permissions;

	permissions = O_RDONLY;
	if (type == IN_READFILE)
	{
		*fd = open(filename, permissions);
		if (*fd == -1)
			return (3);
	}
	return (0);
}

/**
	@brief Makes correct fd assignment according to redirect type (<, >, <<, >>).
		Sets error flag in case of failure.
	@param cmd Redirect command.
	@param fd Pointer to file descriptor structure for redirect stdin and stdout
		between children.
	@param fd_docks File descriptors from heredocs.
	@param err_fl Pointer to error flag.
	@return None.
*/
static void	ft_redirect_type_fd_assign(t_command *cmd, t_fd *fd, \
	int *fd_docks, int *err_fl)
{
	if (!(ft_strcmp(cmd->comm_table[0], ">")))
	{
		close((fd->out)[1]);
		*err_fl = out_redirect(cmd->comm_table[1], OUT_WRITE, &((fd->out)[1]));
	}
	else if (!(ft_strcmp(cmd->comm_table[0], ">>")))
	{
		close((fd->out)[1]);
		*err_fl = out_redirect(cmd->comm_table[1], OUT_APPEND, &((fd->out)[1]));
	}
	else if (ft_strcmp(cmd->comm_table[0], "<") == 0)
	{
		if (fd_docks == NULL)
			close((fd->in)[0]);
		else if ((fd->in)[0] != fd_docks[0])
			close((fd->in)[0]);
		*err_fl = in_redirect(cmd->comm_table[1], IN_READFILE, &((fd->in)[0]));
	}
	else if (!(ft_strcmp(cmd->comm_table[0], "<<")) && fd_docks != NULL)
	{
		if ((fd->in)[0] != fd_docks[0])
			close((fd->in)[0]);
		(fd->in)[0] = fd_docks[0];
	}
}

/**
	@brief Redirects the file descriptors to be stdin/stdout and closes all
		still opened file descriptors.
	@param fd_docks File descriptors from heredocs.
	@param fd File descriptor structure for redirect stdin and stdout
		between children.
	@return 1 on error else 0.
*/
static int	ft_fc_closing(int *fd_docks, t_fd fd)
{
	int	error_flag;

	error_flag = 0;
	if (fd_docks != NULL)
		if (fd.in[0] != fd_docks[0])
			close(fd_docks[0]);
	if (dup2(fd.in[0], STDIN_FILENO) == -1)
		error_flag = 1;
	if (dup2(fd.out[1], STDOUT_FILENO) == -1)
		error_flag = 1;
	close(fd.in[0]);
	close(fd.out[1]);
	return (error_flag);
}

/**
	@brief Closes file desriptor in regards to given error_flag.
	@param error_flag Error flag that indicates which file desriptor
		has to be closed (2 for outfile error, 3 on infile error).
	@param fd File descriptor structure for redirect stdin and stdout
		between children.
	@return Returns passed error_flag.
*/
static int	ft_fc_error_exit(int error_flag, t_fd fd)
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
	@brief Checks for redirections in the cmd index and calls 
		function to open the given file and overwrites current
		stdin and stdout of child.(ft_file_checker)
	@param cmd_list Array of strings with commands and their
		respective flags and arguments.
	@param i Index for child pid.
	@param fd File descriptor structure for redirect stdin and stdout
		between children.
	@param fd_docks File descriptors from heredocs.
	@return Returns error_flag from file descriptor closing.
		1 on error else 0.
*/
static int	ft_fc(t_list **cmd_list, int i, t_fd fd, int *fd_docks)
{
	t_command	*cmd;
	int			error_flag;

	cmd = NULL;
	error_flag = 0;
	while (*cmd_list != NULL)
	{
		cmd = (t_command *)(*cmd_list)->content;
		if (cmd->index != i)
			break ;
		if (cmd->cmd_type == FT_CMD_TYPE_REDIRECT)
		{
			ft_redirect_type_fd_assign(cmd, &fd, fd_docks, &error_flag);
			if (ft_fc_error_exit(error_flag, fd) != 0)
				return (error_flag);
		}
		else
			break ;
		*cmd_list = (*cmd_list)->next;
	}
	return (ft_fc_closing(fd_docks, fd));
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
void	ft_pipex_execute_child(t_list *cmd_list, char **envp, pid_t pid)
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
	@brief Initiates and allocates memory for  the heredoc file desriptors and
		creates the pipe on them for heredoc execution.
	@param fd_docks Pointer to file descriptors from heredocs.
	@param fd_stream File descprictors for terminal streams.
	@param index Index in command list of the command to be executed.
	@return None.
	@exception If heredoc file descriptors already exist they are first closed
		and free befor created again.
*/
static void	ft_heredoc_pipe_init(int **fd_docks, int fd_stream[2], int index)
{
	if (fd_docks[index] != NULL)
	{
		close(fd_docks[index][0]);
		free(fd_docks[index]);
	}
	fd_docks[index] = (int *)malloc(sizeof(int) * 2);
	if (pipe(fd_docks[index]) == -1)
		ft_err_par(FT_ERROR_PIPEX_PIPE_FAIL, fd_docks, fd_stream, NULL);
}

/**
	@brief Frees heredoc filedesriptors and global variables and 
		afterwards exits the heredoc child process.
	@param fd_docks Pointer to file descriptors from heredocs.
	@return None.
*/
static void	ft_heredoc_child_free(int **fd_docks)
{
	ft_free_heredoc_fds(fd_docks);
	free_global();
	exit (0);
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
				heredoc_parent(fd_docks[cmd->index], pid);
		}
		cmd_list = cmd_list->next;
	}
	return (fd_docks);
}

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
	@brief In case of errorin child process the in and out file
		descriptors are closed.
	@param error_flag Inidcates of an error occured.
	@param fd File descriptor structure for redirect stdin and stdout
		between children.
	@return None.
*/
static void	ft_pipex_child_in_out_error(int error_flag, t_fd fd)
{
	if (error_flag == 1)
	{
		close(fd.in[0]);
		close(fd.in[1]);
		close(fd.out[0]);
		close(fd.out[1]);
	}
}

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
static void	ft_pipex_clean_child_exec(t_list *cmd_list, \
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
static void	ft_pipex_parent_exec(t_list **cmd_list, t_fd fd, int i, int *pidt)
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
static void	ft_ch_err_fl(int error_flag, int **fd_docks, \
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
	@brief Increments the necessary values for looping through 
		the commands in cmd_list.
	@param i Pointer to index for child pids.
	@param cmd_list Array of strings with commands and their
		respective flags and arguments.
	@return None.
*/
static void	ft_pipex_iterator(int *i, t_list **cmd_list)
{
	(*i)++;
	if (*cmd_list)
		*cmd_list = (*cmd_list)->next;
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
static void	ft_pipex(int fd_s[2], char **envp, int **fd_d, pid_t *pidt)
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

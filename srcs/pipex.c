#include "../incl/minishell.h"

/* void	ft_initialize_fds(int (*fd_temp)[2])
{
	dup2(STDIN_FILENO, (*fd_temp)[0]);
	dup2(STDOUT_FILENO, (*fd_temp)[1]);
} */

void	ft_initialize_fds(int *fd_temp)
{
	dup2(STDIN_FILENO, fd_temp[0]);
	dup2(STDOUT_FILENO, fd_temp[1]);
}

int out_redirect(char* filename, int type, int *fd)
{
	int permissions;

	permissions = 0;
	if (type == OUT_WRITE)
		permissions = O_WRONLY | O_CREAT | O_TRUNC;
	else if (type == OUT_APPEND)
		permissions =  O_WRONLY | O_APPEND | O_CREAT ;
	*fd = open(filename, permissions, 0777);
	if (*fd == -1)
		return (2);
	return (0);
}

int in_redirect(char* filename, int type,  int *fd)
{
	int permissions;

	permissions = O_RDONLY;
	if (type == IN_READFILE)
	{
		*fd = open(filename, permissions);
		if (*fd == -1)
			return(3);
	}
	return (0);
}

static int	ft_file_checker(t_list **cmd_list, int i, t_fd fd, int *fd_docks)
{
	t_command *cmd;
	int error_flag;

	cmd = NULL;
	error_flag = 0;
	while (*cmd_list != NULL)
	{
		cmd = (t_command *)(*cmd_list)->content;
		if (cmd->index != i) //index has to start from zero
			break;
		if (cmd->cmd_type == FT_CMD_TYPE_REDIRECT)
		{
			if (!(ft_strcmp(cmd->comm_table[0], ">")))
			{
				close(fd.out[1]);
				error_flag = out_redirect(cmd->comm_table[1], OUT_WRITE, &(fd.out[1]));
			}
			else if (!(ft_strcmp(cmd->comm_table[0], ">>")))
			{
				close(fd.out[1]);
				error_flag = out_redirect(cmd->comm_table[1], OUT_APPEND, &(fd.out[1]));
			}
			else if(ft_strcmp(cmd->comm_table[0], "<") == 0 )
			{
				if (fd_docks == NULL)
					close(fd.in[0]);
				else
					if(fd.in[0] != fd_docks[0])
						close(fd.in[0]);					
				error_flag = in_redirect(cmd->comm_table[1], IN_READFILE, &(fd.in[0]));
			}
			else if(!(ft_strcmp(cmd->comm_table[0], "<<")) && fd_docks != NULL)
			{
				if(fd.in[0] != fd_docks[0])
					close(fd.in[0]);
				fd.in[0] = fd_docks[0];
			}
			if (error_flag != 0)
				return (error_flag);
		}
		else
			break;
		*cmd_list = (*cmd_list)->next;
	}
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

void	ft_execute_child(t_list *cmd_list, char **envp, pid_t pid)
{
	t_command *cmd;
	if (cmd_list != NULL)
		cmd = (t_command *)(cmd_list->content);
	else
		return ;

	if (cmd->cmd_type == FT_CMD_TYPE_SYSTEM)
		if (execve(cmd->path,cmd->comm_table, envp) == -1)
			ft_pipex_error_handler_child(FT_ERROR_PIPEX_EXEC_FAIL, NULL, NULL, NULL);
	if (cmd->cmd_type == FT_CMD_TYPE_BUILT_IN)
	{
		ft_execve(cmd->comm_table, pid);
	}
}


static int **ft_heredoc_init(t_list *cmd_list, int last_index, int fd_stream[2])
{
	int			**fd_docks;
	pid_t		pid;
	t_command	*cmd;

	fd_docks = ft_calloc(last_index + 1, sizeof(int *));
	while(cmd_list != NULL)
	{
		cmd = (t_command *)cmd_list->content;
		if (!ft_strcmp(cmd->comm_table[0], "<<") && cmd->cmd_type == FT_CMD_TYPE_REDIRECT)
		{
			if(fd_docks[cmd->index] != NULL)
			{
				close(fd_docks[cmd->index][0]);
				free(fd_docks[cmd->index]);
			}
			fd_docks[cmd->index] = (int *)malloc(sizeof(int) * 2);
			if (pipe(fd_docks[cmd->index]) == -1)
				ft_pipex_error_handler_parent(FT_ERROR_PIPEX_PIPE_FAIL, fd_docks, fd_stream, NULL);
			pid = fork();
			if (!pid)
			{
				heredoc_child(fd_docks[cmd->index], fd_stream, cmd->comm_table[1], "> ");
				ft_free_heredoc_fds(fd_docks);
				exit (0);
			}
			else
				heredoc_parent(fd_docks[cmd->index], pid);
		}
		cmd_list = cmd_list->next;
	}
	return (fd_docks);
}

static void ft_pipex_parent_free(int last_index, int **fd_docks, pid_t *pidt, int fd_stream[2])
{
	int x = 0;
	int status;
	while (x <= last_index)
	{
		waitpid(pidt[x], &status, 0);
		ft_smart_free((void **)&(g_access.last_return));
		g_access.last_return = ft_itoa(WEXITSTATUS(status));
		x++;
	}
	dup2(fd_stream[0], STDIN_FILENO);
	dup2(fd_stream[1], STDOUT_FILENO);
	ft_free_heredoc_fds(fd_docks);
	ft_smart_free((void **)&pidt);
}

static int ft_pipex_child_in_out_init(t_fd fd, int fd_stream[2], int i, int last_index)
{
	int error_flag;

	error_flag = 0;
	close(fd.out[0]);
	if (i == 0)
		if (dup2(fd_stream[0], fd.in[0]) == -1)
			error_flag = 1;
	if (i == last_index)
		if (dup2(fd_stream[1], fd.out[1]) == -1)
			error_flag = 1;
	if (dup2(fd.in[0], STDIN_FILENO) == -1)
		error_flag = 1;
	if (dup2(fd.out[1], STDOUT_FILENO) == -1)
		error_flag = 1;
	if (error_flag == 1)
	{
		close(fd.in[0]);
		close(fd.in[1]);
		close(fd.out[0]);
		close(fd.out[1]);
	}
	return (error_flag);
}

static void ft_pipex_exit_handler_child(t_list *cmd_list, char **envp, pid_t *pidt, int i)
{
	int exit_value;
	int current_pidt;

	current_pidt = pidt[i];
	ft_smart_free((void **)&pidt);
	ft_execute_child(cmd_list, envp, current_pidt);
	exit_value = ft_atoi(g_access.last_return);
	free_global();
	close(STDERR_FILENO);
	close(STDIN_FILENO);
	close(STDOUT_FILENO);
	exit(exit_value);
}

static void ft_pipex_parent_execution(t_list **cmd_list, t_fd fd, int i, int *pidt)
{
	int last_index;
	t_command *cmd;

	last_index = ((t_command *)ft_lstlast(g_access.parser2exec)->content)->index;
	if (i == 0)
		close(fd.in[1]);
	while (*cmd_list != NULL)
	{
		cmd = (t_command *)(*cmd_list)->content;
		if (cmd->cmd_type != FT_CMD_TYPE_REDIRECT)
			break;
		*cmd_list = (*cmd_list)->next;
	}
	if (cmd->cmd_type == FT_CMD_TYPE_BUILT_IN)
		ft_execve(cmd->comm_table, pidt[i]);
	close(fd.in[0]);
	close(fd.out[1]);
	if (i == last_index)
		close(fd.out[0]);
}

static pid_t *ft_pipex(int fd_stream[2], char **envp, int **fd_docks, int last_index)
{
	pid_t *pidt;
	int i;
	t_fd	fd;
	t_list *cmd_list;
	int error_flag;

	i = 0;
	cmd_list = g_access.parser2exec;
	if (pipe(fd.out) == -1)
		ft_pipex_error_handler_parent(FT_ERROR_PIPEX_PIPE_FAIL, fd_docks, fd_stream, NULL);
	fd.in[1] = fd.out[1];
	pidt = ft_calloc(last_index + 1, sizeof(int *));
	while (cmd_list != NULL)
	{
		fd.in[0] = fd.out[0];
		if (pipe(fd.out) == -1)
			ft_pipex_error_handler_parent(FT_ERROR_PIPEX_PIPE_FAIL, fd_docks, fd_stream, pidt);
		pidt[i] = fork();
		if (pidt[i] == -1)
			ft_pipex_error_handler_parent(FT_ERROR_PIPEX_FORK_FAIL, fd_docks, fd_stream, pidt);
		else if(pidt[i] == 0)
		{
			if (ft_pipex_child_in_out_init(fd, fd_stream, i, last_index))
				ft_pipex_error_handler_child(FT_ERROR_PIPEX_FD_DUP_FAIL, fd_docks, fd_stream, pidt);
			error_flag = ft_file_checker(&cmd_list, i, fd, fd_docks[i]);
			if (error_flag == 1)
				ft_pipex_error_handler_child(FT_ERROR_PIPEX_FD_DUP_FAIL, fd_docks, fd_stream, pidt);
			else if (error_flag == 2)
			{
				if(i == 0)
					close(fd.in[1]);
				close(fd.in[0]);
				ft_pipex_error_handler_child(FT_ERROR_PIPEX_OUTFILE_FAIL, fd_docks, fd_stream, pidt);
			}
			else if(error_flag == 3)
			{
				if(i == 0)
					close(fd.in[1]);
				close(fd.out[1]);
				ft_pipex_error_handler_child(FT_ERROR_PIPEX_INFILE_FAIL, fd_docks, fd_stream, pidt);
			}
			if(i == 0)
				close(fd.in[1]);
			ft_free_heredoc_fds(fd_docks);
			ft_pipex_exit_handler_child(cmd_list, envp, pidt, i);
		}
		else
			ft_pipex_parent_execution(&cmd_list, fd, i, pidt);
		i++;
		if (cmd_list)
			cmd_list = cmd_list->next;
	}
	return (pidt);
}

int ft_executor(char** envp)
{
	int fd_stream[2];
	pid_t *pidt;
	int		**fd_docks;
	int last_index;

	fd_stream[0] = 0;
	fd_stream[1] = 0;

	ft_initialize_fds(fd_stream);
	last_index = ((t_command *)ft_lstlast(g_access.parser2exec)->content)->index;
	fd_docks = ft_heredoc_init(g_access.parser2exec, last_index, fd_stream);
	pidt = ft_pipex(fd_stream, envp, fd_docks, last_index);
	ft_pipex_parent_free(last_index, fd_docks, pidt, fd_stream);
	ft_free_linked_list(&g_access.parser2exec, FT_LIST_TYPE_COMMAND, 1);
	return (1);
}

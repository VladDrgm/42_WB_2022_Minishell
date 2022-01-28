#include "../incl/pipex.h"

# define OUT_WRITE 0
# define OUT_APPEND 1
# define IN_READFILE 2
# define IN_HEREDOC 3

void	ft_pipex(int argc, char **argv, t_list *cmd_list, char **envp)
{
	int		fd[2];
	pid_t	pid[argc - 3];
	int		i;
	int		fd_stream[2];

	i = 0;
	//function to copy streams
	ft_initialize_fds(fd, argc, argv, cmd_list, fd_stream);
	while (i <= argc - 3 - 1)
	{
		if (pipe(fd) == -1)
			ft_exit_on_error(&cmd_list, "Pipe creation failed");
		pid[i] = fork();
		if (pid[i] == -1)
			ft_exit_on_error(&cmd_list, "Forking failed");
		else if (pid[i] == 0)
			ft_execute_child_process(cmd_list, envp, fd, fd_stream);
		else
		{
			if (i == argc - 3 - 1)
				ft_execute_last_cmd(fd, &cmd_list, pid[i], fd_stream);
			else
				ft_execute_parent_process(fd, &cmd_list, pid[i]);
			if (cmd_list->next != NULL)
				cmd_list = cmd_list->next;
			i++;
		}
	}
	i = 0;
	while (i <= argc - 3 - 1)
	{
		waitpid(pid[i], NULL, 0);
		i++;
	}
	write(2, "\nEND\n", 5);
}

void heredoc(char *stop_word, int fd_stream[2], int fd_out)
{
	char *out;
	dup2(fd_stream[0], STDIN_FILENO);
	dup2(fd_stream[1], STDOUT_FILENO);
	while(1)
	{
		out = readline("<HEREDOC> ");
		if (out == NULL)
			break;
		if (!strcmp(out, stop_word)) // change to ft fuinction
		{
			free (out);
			break;
		}
		write(fd_out, out, ft_strlen(out));
		write(fd_out, "\n", 1);
		free(out);
	}
	close(fd_out);
	if (close(fd_stream[0]) == -1)
		ft_exit_on_error2("Close of fd[0] failed6");
	if (close(fd_stream[1]) == -1)
		ft_exit_on_error2("Close of fd[0] failed7");
	if (close(STDIN_FILENO) == -1)
		ft_exit_on_error2("Close of fd[0] failed6");
	if (close(STDOUT_FILENO) == -1)
		ft_exit_on_error2("Close of fd[0] failed7");
	exit(0) ;
}



void in_redirect(char* filename, int type, int fd_stream[2])
{
	int fd[2];
	int premissions;
	pid_t pid;
	
	premissions = O_RDONLY;
	if(type != IN_HEREDOC && type != IN_READFILE)
	{
		ft_exit_on_error2("Wrong type U moron\n");
		return;
	}
	if (type == IN_READFILE)
	{
		fd[0] = open(filename, premissions, 0777);
		if (fd[0] == -1)
			ft_exit_on_error2("Error on opening input file");
		if (dup2(fd[0], STDIN_FILENO) == -1)
			ft_exit_on_error2("File descriptor duplication failed1");
		if (close(fd[0]) == -1)
			ft_exit_on_error2("Close of fd failed");
	}
	else
	{
		pipe(fd);
		if (dup2(fd[0], STDIN_FILENO) == -1)
			ft_exit_on_error2("File descriptor duplication failed2");
		pid = fork();
		if (pid == 0)
			heredoc(filename, fd_stream, fd[1]);
		close(fd[1]);
		waitpid(pid,NULL,0);
			
	}
}	


void out_redirect(char* filename, int type)
{
	int fd;
	int premissions;
	
	if (type == OUT_WRITE)
		premissions = O_WRONLY | O_CREAT | O_TRUNC;
	else if (type == OUT_APPEND)
		premissions =  O_WRONLY | O_APPEND | O_CREAT ;
	else
	{
		ft_exit_on_error2("Wrong type U moron\n");
		return;
	}
	fd = open(filename, premissions, 0777);
	if (fd == -1)
		ft_exit_on_error2("Error on opening input file3");
	if (dup2(fd, STDOUT_FILENO) == -1)
		ft_exit_on_error2("File descriptor duplication failed4");
	if (close(fd) == -1)
		ft_exit_on_error2("Close of fd failed");
}

void	ft_initialize_fds(int *old, int argc, char **argv, t_list *cmd_list, int *fd_temp)
{
	//int fd[2];

	old++;
	argc++;
	argv++;
	if (dup2(STDIN_FILENO, fd_temp[0]) == -1)
		ft_exit_on_error(&cmd_list, "File descriptor duplication failed");
	if (dup2(STDOUT_FILENO, fd_temp[1]) == -1)
		ft_exit_on_error(&cmd_list, "File descriptor duplication failed");
	/*fd[0] = open(argv[1], O_RDONLY);
	if (fd[0] == -1)
		ft_exit_on_error(&cmd_list, "Error on opening input file");
	fd[1] = open(argv[argc -1], O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (fd[1] == -1)
		ft_exit_on_error(&cmd_list, "Error on opening output file");
	if (dup2(fd[0], STDIN_FILENO) == -1)
		ft_exit_on_error(&cmd_list, "File descriptor duplication failed");
	if (dup2(fd[1], STDOUT_FILENO) == -1)
		ft_exit_on_error(&cmd_list, "File descriptor duplication failed");
	if (close(fd[0]) == -1)
		ft_exit_on_error(&cmd_list, "Close of fd[0] failed");
	if (close(fd[1]) == -1)
		ft_exit_on_error(&cmd_list, "Close of fd[1] failed");*/

}

void	ft_execute_child_process(t_list *cmd_list, char **envp, int *fd, int *fd_stream)
{
	if (dup2(fd[1], STDOUT_FILENO) == -1)
		ft_exit_on_error(&cmd_list, "File descriptor duplication failed0");
	if (close(fd[0]) == -1)
		ft_exit_on_error(&cmd_list, "Close of fd[0] failed1");
	if (close(fd[1]) == -1)
		ft_exit_on_error(&cmd_list, "Close of fd[1] failed2");
	in_redirect("stop", IN_HEREDOC, fd_stream);
	if (execve(((t_content *)(cmd_list->content))->path, \
		((t_content *)(cmd_list->content))->cmd_n_flags, envp) == -1)
		ft_exit_on_error(&cmd_list, "Command execution failed");
}

void	ft_execute_parent_process(int *fd, t_list **cmd_list, pid_t pid)
{
	waitpid(pid, NULL, 0);
	errno = 0;
	if (dup2(fd[0], STDIN_FILENO) == -1)
		ft_exit_on_error(cmd_list, "File descriptor duplication failed");
	if (close(fd[0]) == -1)
		ft_exit_on_error(cmd_list, "Close of fd[0] failed3");
	if (close(fd[1]) == -1)
		ft_exit_on_error(cmd_list, "Close of fd[1] failed4");
}

void	ft_execute_last_cmd(int *fd, t_list **cmd_list, pid_t pid, int *fd_temp)
{
	char c;

	waitpid(pid, NULL, 0);

	errno = 0;
	if (dup2(fd_temp[0], STDIN_FILENO) == -1)
		ft_exit_on_error(cmd_list, "File descriptor duplication failed");
	if (dup2(fd_temp[1], STDOUT_FILENO) == -1)
		ft_exit_on_error(cmd_list, "File descriptor duplication failed");
	if (close(fd[1]) == -1)
		ft_exit_on_error(cmd_list, "Close of fd[1] failed");
	while (read(fd[0], &c, 1))
		write(1, &c, 1);
	if (close(fd[0]) == -1)
		ft_exit_on_error(cmd_list, "Close of fd[0] failed5");
	if (close(fd_temp[0]) == -1)
		ft_exit_on_error(cmd_list, "Close of fd[0] failed6");
	if (close(fd_temp[1]) == -1)
		ft_exit_on_error(cmd_list, "Close of fd[0] failed7");
}

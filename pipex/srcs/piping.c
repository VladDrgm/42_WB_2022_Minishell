#include "../incl/pipex.h"

# define OUT_WRITE 0
# define OUT_APPEND 1
# define IN_READFILE 2
# define IN_HEREDOC 3

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
		//write(2, out, ft_strlen(out));
		//write(2, "\n", 1);
		free(out);
	}
	if (close(fd_out) == -1)
		ft_exit_on_error2("Close of fd[0] failed10");
	/*if (close(fd_stream[0]) == -1)
		ft_exit_on_error2("Close of fd[0] failed11");
	if (close(fd_stream[1]) == -1)
		ft_exit_on_error2("Close of fd[0] failed12");*/
	/*if (close(STDIN_FILENO) == -1)
		ft_exit_on_error2("Close of fd[0] failed13");
	if (close(STDOUT_FILENO) == -1)
		ft_exit_on_error2("Close of fd[0] failed14");*/
	exit(0) ;
}


void	ft_pipex(t_list *cmd_list, char **envp)
{
	int		fd[2];
	pid_t	pid[0];
	pid_t	pid_h;
	int		fd_stream[2];
	int		**fd_docks;
	t_list 	*cmd_list_temp;
	t_list	*temp;
	int i = 0;
	char c;

	ft_initialize_fds(fd_stream);
	//temp = ft_lstlast(cmd_list);
	//fd_docks = calloc(((t_command *)(temp->content))->index, sizeof(int*));
	cmd_list_temp = cmd_list;
	while (cmd_list_temp != NULL)
	{
		if(((t_command*)(cmd_list_temp->content))->cmd_type == 2)
		{
			if(!strcmp(((t_command*)(cmd_list_temp->content))->comm_table[0], "<<"))
			{
				if(fd_docks[((t_command*)(cmd_list_temp->content))->index] != NULL)
				{
					close(fd_docks[((t_command*)(cmd_list_temp->content))->index][0]);
					free(fd_docks[((t_command*)(cmd_list_temp->content))->index]);
				}
				//fd_docks[((t_command*)(cmd_list_temp->content))->index] = (int *)malloc(sizeof(int) * 2);
				//if (pipe(fd_docks[((t_command*)(cmd_list_temp->content))->index]) == -1)
				//	ft_exit_on_error(&cmd_list, "Pipe creation failed");
				write(2, "LOOP\n", 5);
				pipe(fd);
				int temp = read(fd[1], &c, 1);
				printf("HERE %d\n", temp);
				pid_h = fork();
				if (pid_h == 0)
				{
					//close(fd_docks[((t_command*)(cmd_list_temp->content))->index][1]);
					//heredoc(((t_command*)(cmd_list_temp->content))->comm_table[1], fd_stream, fd_docks[((t_command*)(cmd_list_temp->content))->index][0]);
					//close(fd[1]);
					//heredoc(((t_command*)(cmd_list_temp->content))->comm_table[1], fd_stream, fd[0]);
					write(fd[0], "HAHA\n", 5);
					//close(fd[0]);
					//write(0, "HAHA\n", 5);
					while(1);
				}
				else
				{
					//close(fd_docks[((t_command*)(cmd_list_temp->content))->index][0]);
					//waitpid(pid_h, NULL, 0);
					//close(fd[0]);
					//while(read(fd_docks[((t_command*)(cmd_list_temp->content))->index][1], &c, 1))
					//	write(1, &c, 1);
					int temp = read(fd[1], &c, 1);
					while(temp)
					{
						write(1, &c, 1);
						printf("HERE %d\n", temp);
						temp = read(fd[1], &c, 1);
						if (temp <= 0)
							break;
					}
				}
			}
		}
		cmd_list_temp = cmd_list_temp->next;
	}
	//function to copy streams
	while (cmd_list != NULL)
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
			waitpid(pid[i], NULL, 0);
			if (cmd_list->next == NULL)
				ft_execute_last_cmd(fd, &cmd_list, pid[i], fd_stream);
			else
				ft_execute_parent_process(fd, &cmd_list, pid[i]);
			cmd_list = cmd_list->next;
			i++;
		}
	}
	i = 0;
	/*while (i <= argc - 3 - 1)
	{
		waitpid(pid[i], NULL, 0);
		i++;
	}*/
	write(2, "\nEND\n", 5);
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

void	ft_initialize_fds(int *fd_temp)
{

	//if (dup2(STDIN_FILENO, fd_temp[0]) == -1)
	//	ft_exit_on_error(&cmd_list, "File descriptor duplication failed");
	//if (dup2(STDOUT_FILENO, fd_temp[1]) == -1)
	//	ft_exit_on_error(&cmd_list, "File descriptor duplication failed");
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
	fd_stream++;
	if (dup2(fd[1], STDOUT_FILENO) == -1)
		ft_exit_on_error(&cmd_list, "File descriptor duplication failed0");
	if (close(fd[0]) == -1)
		ft_exit_on_error(&cmd_list, "Close of fd[0] failed1");
	if (close(fd[1]) == -1)
		ft_exit_on_error(&cmd_list, "Close of fd[1] failed2");
	//in_redirect("stop", IN_HEREDOC, fd_stream);
	//write(2, ((t_command *)(cmd_list->content))->path, strlen(((t_command *)(cmd_list->content))->path));
	if (execve(((t_command *)(cmd_list->content))->path, \
		((t_command *)(cmd_list->content))->comm_table, envp) == -1)
		ft_exit_on_error(&cmd_list, "Command execution failed");
}

/*void	ft_execute_parent_process(int *fd, t_list **cmd_list, pid_t pid)
{
	pid++;
	if (dup2(fd[0], STDIN_FILENO) == -1)
		ft_exit_on_error(cmd_list, "File descriptor duplication failed");
	if (close(fd[0]) == -1)
		ft_exit_on_error(cmd_list, "Close of fd[0] failed3");
	if (close(fd[1]) == -1)
		ft_exit_on_error(cmd_list, "Close of fd[1] failed4");
}*/

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
	/*if (close(fd_temp[1]) == -1)
		ft_exit_on_error(cmd_list, "Close of fd[0] failed7");*/
}

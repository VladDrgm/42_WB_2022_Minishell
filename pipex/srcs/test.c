#include "../incl/pipex.h"
# include <limits.h>
# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include <fcntl.h>
# include <errno.h>
# include <sys/wait.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
#include <sys/types.h>
#include <unistd.h>
#include <signal.h>


void	ft_initialize_fds(int *fd_temp)
{

	dup2(STDIN_FILENO, fd_temp[0]);
	dup2(STDOUT_FILENO, fd_temp[1]);
}

void parent(int *fd, pid_t pid)
{
	char c;

	waitpid(pid, NULL, 0);
	close(fd[1]);
	// while(read(fd[0], &c, 1))
	// 	write(1, &c, 1);
	// close(fd[0]);
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
		write(fd_out, out, strlen(out));
		write(fd_out, "\n", 1);
		//write(2, out, ft_strlen(out));
		//write(2, "\n", 1);
		free(out);
	}
	close(fd_out);
	close(fd_stream[0]);
	close(fd_stream[1]);
	close(STDIN_FILENO);
	close(STDOUT_FILENO);
}

void child(int* fd, int *fd_stream, char *stop_name)
{
	close(fd[0]);
	heredoc(stop_name, fd_stream, fd[1]);
	exit(0);
}

int out_redirect(char* filename, int type)
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
		return -1;
	}
	fd = open(filename, premissions, 0777);
	dprintf(2, "Value of fd in outredirect is %d\n", fd);
	if (fd == -1)
		ft_exit_on_error2("Error on opening input file3");
	// if (dup2(fd, STDOUT_FILENO) == -1)
	// 	ft_exit_on_error2("File descriptor duplication failed4");
	// if (close(fd) == -1)
	// 	ft_exit_on_error2("Close of fd failed");
	return fd;
}

int in_redirect(char* filename, int type)
{
	int fd;
	int premissions;
	pid_t pid;

	premissions = O_RDONLY;
	if(type != IN_HEREDOC && type != IN_READFILE)
	{
		ft_exit_on_error2("Wrong type U moron\n");
		return -1;
	}
	if (type == IN_READFILE)
	{
		fd = open(filename, premissions, 0777);
		if (fd == -1)
		{
			ft_exit_on_error2("Error on opening input file");
		}

		// if (dup2(fd[0], STDIN_FILENO) == -1)
		// 	ft_exit_on_error2("File descriptor duplication failed1");
		// if (close(fd[0]) == -1)
		// 	ft_exit_on_error2("Close of fd failed");
	}
	return fd;
}

void ft_execute_parent(void)
{
	printf("Im executing a parents as well FBI!\n");
}

void	ft_file_checker(t_list **cmd_list, int i, int fd_infile, int fd_outfile, int *fd_docks)
{
	t_command *cmd;

	cmd = NULL;
	while (*cmd_list != NULL)
	{
		cmd = (t_command *)(*cmd_list)->content;
		if (cmd->index != i) //index has to start from zero
			break;
		if (cmd->cmd_type == FT_CMD_TYPE_REDIRECT)
		{
			if (!(strcmp(cmd->comm_table[0], ">"))) //comment for system function
			{
				if(fd_outfile != 1)
					close(fd_outfile);
				fd_outfile = out_redirect(cmd->comm_table[1], OUT_WRITE);
			}
			else if (!(strcmp(cmd->comm_table[0], ">>"))) //comment for system function
			{
				if(fd_outfile != 1)
					close(fd_outfile);
				fd_outfile = out_redirect(cmd->comm_table[1], OUT_APPEND);
			}
			else if(strcmp(cmd->comm_table[0], "<") == 0 ) //comment for system function
			{
				if (fd_docks != NULL)
				{
					if(fd_infile != 0 || fd_infile != fd_docks[0])
						close(fd_infile);
				}
				else
				{
					if(fd_infile != 0)
						close(fd_infile);
				}
				fd_infile = in_redirect(cmd->comm_table[1], IN_READFILE);
			}
			else if(!(strcmp(cmd->comm_table[0], "<<")) && fd_docks != NULL) //comment for system function
			{
				char c;

				if(fd_infile != 0 || fd_infile != fd_docks[0])
					close(fd_infile);
				fd_infile = fd_docks[0];
			}

		}

		*cmd_list = (*cmd_list)->next;
	}
	if (fd_docks != NULL)
		if (fd_infile != fd_docks[0])
			close(fd_docks[0]);
	if (dup2(fd_infile, STDIN_FILENO) == -1)
		ft_exit_on_error2("File descriptor duplication failed 53");
	if (dup2(fd_outfile, STDOUT_FILENO) == -1)
		ft_exit_on_error2("File descriptor duplication failedi 54");
	close(fd_infile);
	close(fd_outfile);
}

void	ft_execute_child(t_list *cmd_list, char **envp)
{
	t_command *cmd;

	cmd = (t_command *)cmd_list->content;
	if (cmd->cmd_type == FT_CMD_TYPE_SYSTEM)
		if (execve(cmd->path,cmd->comm_table, envp) == -1)
			ft_exit_on_error(&cmd_list, "Command execution failed");
	// add built-ins call
}

int test(t_list *cmd_list, char** envp)
{
	int fd[2];
	int fd_stream[2];
	pid_t *pidt;
	t_command *cmd;
	t_list *cmd_list_temp;
	int		**fd_docks;
	char *out;
	int i;
	int fd_in[2];
	int fd_out[2];
	int last_index;

	cmd_list_temp = NULL;
	ft_initialize_fds(fd_stream);
	last_index = ((t_command *)ft_lstlast(cmd_list)->content)->index;
	cmd_list_temp = cmd_list;
	fd_docks = calloc(last_index, sizeof(int *));  //system function
	i = 0;
	while(cmd_list_temp != NULL)
	{
		cmd = (t_command *)cmd_list_temp->content;
		if (!strcmp(cmd->comm_table[0], "<<") && cmd->cmd_type == FT_CMD_TYPE_REDIRECT)  //system function
		{
			if(fd_docks[cmd->index] != NULL)
			{
				close(fd_docks[cmd->index][0]);
				free(fd_docks[cmd->index]);
			}
			fd_docks[cmd->index] = (int *)malloc(sizeof(int) * 2);
			if (pipe(fd_docks[cmd->index]) == -1)
				ft_exit_on_error(&cmd_list, "Pipe creation failed");
			// pipe(fd);
			pid_t pid = fork();
			if (!pid)
				// child(fd, fd_stream, cmd->comm_table[1]);
				child(fd_docks[cmd->index], fd_stream, cmd->comm_table[1]);
			else
				// parent(fd, pid);
				parent(fd_docks[cmd->index], pid);
		}
		cmd_list_temp = cmd_list_temp->next;
	}
	if (pipe(fd_out) == -1)
			ft_exit_on_error(&cmd_list, "Pipe creation failed in line 116");
	fd_in[1] = fd_out[1];
	pidt = calloc(last_index, sizeof(int *)); //system function
	while (cmd_list != NULL)
	{
		fd_in[0] = fd_out[0];
		if (pipe(fd_out) == -1)
			ft_exit_on_error(&cmd_list, "Pipe creation failed in line 124");
		pidt[i] = fork();
		if (pidt[i] == -1)
			ft_exit_on_error(&cmd_list, "Pipe creation failed in line 127");
		else if(pidt[i] == 0)
		{
			close(fd_in[1]);
			//char c4;
			// while (read(fd_in[0], &c4, 1))
			// {
			// 	write(1, &c4, 1);
			// }
			if (dup2(fd_in[0], STDIN_FILENO) == -1)
				ft_exit_on_error2("File descriptor duplication failed 90");
			if (dup2(fd_out[1], STDOUT_FILENO) == -1)
				ft_exit_on_error2("File descriptor duplication failedi 91");
			ft_file_checker(&cmd_list, i, fd_in[0], fd_out[1], fd_docks[i]);
			// char c;
			// while (read(STDIN_FILENO, &c, 1))
			// {
			// 	write(1, &c, 1);
			// }
			// exit(0);
			ft_execute_child(cmd_list, envp);
			exit(0);
		}
		else
		{
			if (i == 0)
			{
				// while(1)
				// {
				// 	out = readline("ll>");
				// 	if (out == NULL)
				// 		break;
				// 	write(fd_in[1], out, strlen(out));
				// 	write(fd_in[1], "\n", 1);
				// 	free(out);
				// }
				close(fd_in[1]);
			}
			close(fd_in[0]);
			close(fd_out[1]);
			char ccc;
			while (read(fd_out[0], &ccc, 1))
			{
				write(1, &ccc, 1);
			}
			waitpid(pidt[i], NULL, 0);
			ft_execute_parent();
		}

		while (cmd_list != NULL)
		{
			cmd = (t_command *)cmd_list->content;
			if (cmd->index != i)
			{
				break;
			}
			cmd_list = cmd_list->next;
		}
		i++;
	}


}
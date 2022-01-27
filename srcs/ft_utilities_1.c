#include "../incl/pipex.h"
#include "../incl/minishell.h"

void	ft_pid_check(int i)
{
	if (i < 0)
	{
		ft_file_descriptor_killer();
	}
}

void	ft_fd_close(int x, int y)
{
	close(x);
	close(y);
}

void	ft_cmd_exec(t_list *cmd_list, t_helper **help)
{	printf("im exxecuting command\n");
	// if (execve(((t_content *)(cmd_list->content))->path, ((t_content *)(cmd_list->content))->cmd_n_flags, (*help)->envp) == -1)
	if (execve(((t_command *)(cmd_list->content))->path, ((t_command *)(cmd_list->content))->comm_table, (*help)->envp) == -1)
	{
		perror("Command execution failed");
		ft_file_descriptor_killer();
		exit(EXIT_FAILURE);
	}
}

void	ft_setup_help(t_helper **help)
{
	(*help)->pid = 0;
	// (*help)->fd[0] = open(argv[j + 1], O_RDONLY);
	(*help)->fd[0] = 0;
	//  (*help)->fd[0] = dup(STDIN_FILENO);
	// (*help)->fd[1] = open(argv[argc - 1], O_WRONLY | O_CREAT | O_TRUNC, 0777);
	(*help)->fd[1] = 1;
	// (*help)->fd[1] = dup(STDOUT_FILENO);
}

void	ft_dup_close_out(int (*ft)(int, int), int (*fd)(int), int i)
{
	ft(i, STDOUT_FILENO); //dup2 1
	// fd(i); //closing 1
}

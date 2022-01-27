#include "../incl/minishell.h"
#include "../incl/pipex.h"



void	ft_pid_helper1(int (*dp)(int, int), int (*clo)(int), \
				pid_t (*wai)(pid_t, int *, int), t_helper **help)
{
	wai((*help)->pid, NULL, 0);
	// clo((*help)->fd[1]);
	dp((*help)->fd[0], STDIN_FILENO);
	// clo((*help)->fd[0]);
}

// void	ft_pipe(int argc, t_list *cmd_list, t_helper **help)
void	ft_pipe(t_helper **help)
{
	int	i;
	t_list		*cmd_list;

	cmd_list = *g_access.parser2exec;
	i = 0;
	char c;


	// ft_double_safety_check(dup2((*help)->fd[0], 0), dup2((*help)->fd[1], 1));
	// ft_double_close(&close, &close, help);
	// while (i < argc - 3 - 1)
	while (cmd_list)
	{
		ft_pid_helper(&pipe, &fork, help);
		if ((*help)->pid == 0)
		{	write(1, "7\n", 3);
			// close((*help)->fd[0]);
			if (cmd_list->next != NULL)
				ft_dup_close_out(&dup2, &close, (*help)->fd[1]);
			ft_cmd_exec(cmd_list, help);
		}
		else
		{
			ft_pid_helper1(&dup2, &close, &waitpid, help);

			if (cmd_list->next != NULL)
				cmd_list = cmd_list->next;
			i++;
		}
		if (cmd_list->next == NULL)
		{
			write(1, "9\n", 3);
			ft_last_cmd(help);
		}


		cmd_list = cmd_list->next;


	}
	read(STDIN_FILENO, &c, 1);
	// write(1, "10", 2);
	//while (read(STDIN_FILENO, &c, 1));
	// readline("");
	// read(STDIN_FILENO, &c, 1);
}

int	pipex(char **envp)
{

	t_helper	*help;
	// int 	last_index;

	printf("we are here in pipex\n");

	if (FT_PIPES_COMMENT)
	{
		print_list_parse(*g_access.parser2exec);
	}

	// exit(1);

	// cmd_list = NULL;
	help = ft_calloc(sizeof(t_helper), 1);
	help->envp = envp;
	// last_index = ((t_command *)(ft_lstlast(cmd_list)->content))->index;
	// printf("Index is: %d\n", last_index);
	//ft_inputfile_checker(argv[1], argv, argc, &help);
	//ft_outputfile_checker(argv[argc - 1], &help);
	//ft_cmd_check(argv, argc, &help, &cmd_list);
	ft_setup_help(&help);
	//argc is command len
	//ft_pipe(((((t_command *)(cmd_list->content))->comm_len->comm_len, ((t_command *)(cmd_list->content))->comm_table, &help);
	// ft_pipe(((((t_command *)(cmd_list->content))->comm_len->comm_len, ((t_command *)(cmd_list->content))->comm_table, &help);
	ft_pipe(&help);

	return (1);
}

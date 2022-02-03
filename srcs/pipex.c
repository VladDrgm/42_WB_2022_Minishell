#include "../incl/minishell.h"

void make_cmd_list (t_list **cmd_list)
{
	t_command *temp;

	// temp = (t_command *)malloc(sizeof(t_command));
	// temp->comm_len = 3;
	// temp->comm_table = (char **)malloc(sizeof(char *) * temp->comm_len);
	// temp->comm_table[0] = "<<";
	// temp->comm_table[1] = "outhouse2";
	// temp->comm_table[2] = NULL;
	// temp->index = 0;
	// temp->cmd_type = FT_CMD_TYPE_REDIRECT;
	// temp->path= NULL;
	// ft_lstadd_back(cmd_list, ft_lstnew(temp));

	// temp = (t_command *)malloc(sizeof(t_command));
	// temp->comm_len = 3;
	// temp->comm_table = (char **)malloc(sizeof(char *) * temp->comm_len);
	// temp->comm_table[0] = "<<";
	// temp->comm_table[1] = "st";
	// temp->comm_table[2] = NULL;
	// temp->index = 0;
	// temp->cmd_type = FT_CMD_TYPE_REDIRECT;
	// temp->path= NULL;
	// ft_lstadd_back(cmd_list, ft_lstnew(temp));


	// temp = (t_command *)malloc(sizeof(t_command));
	// temp->comm_len = 3;
	// temp->comm_table = (char **)malloc(sizeof(char *) * temp->comm_len);
	// temp->comm_table[0] = "echo";
	// temp->comm_table[1] = "vlad is plumber";
	// temp->comm_table[2] = NULL;
	// temp->index = 0;
	// temp->cmd_type = FT_CMD_TYPE_SYSTEM;
	// temp->path = "/usr/bin/echo";
	// ft_lstadd_back(cmd_list, ft_lstnew(temp));

	// temp = (t_command *)malloc(sizeof(t_command));
	// temp->comm_len = 3;
	// temp->comm_table = (char **)malloc(sizeof(char *) * temp->comm_len);
	// temp->comm_table[0] = "export";
	// temp->comm_table[1] = "ABC+=hehe";
	// temp->comm_table[2] = NULL;
	// temp->index = 0;
	// temp->cmd_type = FT_CMD_TYPE_BUILT_IN;
	// temp->path = NULL;
	// ft_lstadd_back(cmd_list, ft_lstnew(temp));

	// temp = (t_command *)malloc(sizeof(t_command));
	// temp->comm_len = 2;
	// temp->comm_table = (char **)malloc(sizeof(char *) * temp->comm_len);
	// temp->comm_table[0] = "export";
	// // temp->comm_table[1] = "-";
	// temp->comm_table[1] = NULL;
	// temp->index = 1;
	// temp->cmd_type = FT_CMD_TYPE_BUILT_IN;
	// temp->path = NULL;
	// ft_lstadd_back(cmd_list, ft_lstnew(temp));

	// temp = (t_command *)malloc(sizeof(t_command));
	// temp->comm_len = 2;
	// temp->comm_table = (char **)malloc(sizeof(char *) * temp->comm_len);
	// temp->comm_table[0] = "pwd";
	// temp->comm_table[1] = NULL;
	// // temp->comm_table[2] = NULL;
	// temp->index = 1;
	// temp->cmd_type = FT_CMD_TYPE_BUILT_IN;
	// temp->path = NULL;
	// ft_lstadd_back(cmd_list, ft_lstnew(temp));

	// temp = (t_command *)malloc(sizeof(t_command));
	// temp->comm_len = 3;
	// temp->comm_table = (char **)malloc(sizeof(char *) * temp->comm_len);
	// temp->comm_table[0] = "cd";
	// temp->comm_table[1] = "-";
	// temp->comm_table[2] = NULL;
	// temp->index = 2;
	// temp->cmd_type = FT_CMD_TYPE_BUILT_IN;
	// temp->path = NULL;
	// ft_lstadd_back(cmd_list, ft_lstnew(temp));

	// temp = (t_command *)malloc(sizeof(t_command));
	// temp->comm_len = 3;
	// temp->comm_table = (char **)malloc(sizeof(char *) * temp->comm_len);
	// temp->comm_table[0] = ">";
	// temp->comm_table[1] = "stop";
	// temp->comm_table[2] = NULL;
	// temp->index = 1;
	// temp->cmd_type = FT_CMD_TYPE_REDIRECT;
	// temp->path= NULL;
	// ft_lstadd_back(cmd_list, ft_lstnew(temp));

	// 2

	// temp = (t_command *)malloc(sizeof(t_command));
	// temp->comm_len = 3;
	// temp->comm_table = (char **)malloc(sizeof(char *) * temp->comm_len);
	// temp->comm_table[0] = "echo";
	// temp->comm_table[1] = "lala";
	// temp->comm_table[2] = NULL;
	// temp->index = 1;
	// temp->cmd_type = FT_CMD_TYPE_SYSTEM;
	// temp->path = "/usr/bin/echo";
	// ft_lstadd_back(cmd_list, ft_lstnew(temp));

	// temp = (t_command *)malloc(sizeof(t_command));
	// temp->comm_len = 3;
	// temp->comm_table = (char **)malloc(sizeof(char *) * temp->comm_len);
	// temp->comm_table[0] = ">";
	// temp->comm_table[1] = "outhouse";
	// temp->comm_table[2] = NULL;
	// temp->index = 1;
	// temp->cmd_type = FT_CMD_TYPE_REDIRECT;
	// temp->path= NULL;
	// ft_lstadd_back(cmd_list, ft_lstnew(temp));

	// temp = (t_command *)malloc(sizeof(t_command));
	// temp->comm_len = 3;
	// temp->comm_table = (char **)malloc(sizeof(char *) * temp->comm_len);
	// temp->comm_table[0] = "<<";
	// temp->comm_table[1] = "dingus";
	// temp->comm_table[2] = NULL;
	// temp->index = 1;
	// temp->cmd_type = FT_CMD_TYPE_REDIRECT;
	// temp->path= NULL;
	// ft_lstadd_back(cmd_list, ft_lstnew(temp));

	// temp = (t_command *)malloc(sizeof(t_command));
	// temp->comm_len = 3;
	// temp->comm_table = (char **)malloc(sizeof(char *) * temp->comm_len);
	// temp->comm_table[0] = "cat";
	// temp->comm_table[1] = "-e";
	// temp->comm_table[2] = NULL;
	// temp->index = 1;
	// temp->cmd_type = FT_CMD_TYPE_SYSTEM;
	// temp->path = "/usr/bin/cat";
	// ft_lstadd_back(cmd_list, ft_lstnew(temp));

	// temp = (t_command *)malloc(sizeof(t_command));
	// temp->comm_len = 2;
	// temp->comm_table = (char **)malloc(sizeof(char *) * temp->comm_len);
	// temp->comm_table[0] = ">";
	// temp->comm_table[1] = "outhouse";
	// temp->index = 0;
	// temp->cmd_type = FT_CMD_TYPE_REDIRECT;
	// temp->path= NULL;
	// ft_lstadd_back(cmd_list, ft_lstnew(temp));

	//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! the last line should be executable by execve !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
}

int	ft_super_mario(char **envp)
{

	t_list	*cmd_list;
	char *str;
	str = NULL;
	str = "";
	str = "\0";

	cmd_list = NULL;
	/*if (argc < 5)
	{
		ft_putstr_fd("Too few arguments for executing pipex!\n", 1);
		exit(EXIT_FAILURE);
	}*/
	//ft_check_input_file(argv[1], argv[argc - 1]);
	//ft_check_output_file(argv[argc - 1]);
	//ft_make_cmd_list(argv, envp, argc, &cmd_list);
	make_cmd_list(&cmd_list);
	//ft_pipex(cmd_list, envp);
	test(cmd_list, envp);
	return (1);
}


void	ft_check_input_file(char *filename, char *outputfile)
{
	int	fd_output;

	fd_output = 0;
	if (access(filename, F_OK) == 0)
	{
		if (access(filename, R_OK) == 0)
			return ;
		else
		{
			perror("Input file without reading rights");
			fd_output = open(outputfile, O_WRONLY | O_CREAT | O_TRUNC, 0777);
			close(fd_output);
			ft_close_fd();
			exit(EXIT_FAILURE);
		}
	}
	else
	{
		perror("Invalid input file");
		fd_output = open(outputfile, O_WRONLY | O_CREAT | O_TRUNC, 0777);
		close(fd_output);
		ft_close_fd();
		exit(EXIT_FAILURE);
	}
}

void	ft_check_output_file(const char *filename)
{
	if (access(filename, F_OK) == 0)
	{
		if (access(filename, W_OK) != 0)
		{
			perror("Output file without writing rights");
			ft_close_fd();
			exit(EXIT_FAILURE);
		}
	}
	else
		return ;
}

void	ft_make_cmd_list(char **argv, char **envp, int argc, t_list **cmd_list)
{
	t_content	*content;
	t_list		*elem;
	char		**path_list;
	int			j;
	int			i;

	j = 0;
	i = 0;
	path_list = ft_split_path(envp);
	while (i + 2 <= argc - 2)
	{
		content = ft_calloc(1, sizeof(t_content));
		content->cmd_n_flags = ft_split(argv[i + 2], ' ');
		content->path = ft_get_cmd_path(content->cmd_n_flags[0], path_list);
		content->index = j;
		elem = ft_lstnew(content);
		ft_lstadd_back(cmd_list, elem);
		if (content->path == NULL)
			ft_exit_on_invalid_cmd(path_list, cmd_list, content, elem);
		j++;
		i++;
	}
	ft_free_split(path_list);
}

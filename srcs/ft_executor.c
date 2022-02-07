#include "../incl/minishell.h"

//IMPORTANT leave for testing

void make_cmd_list (t_list **cmd_list)
{
	t_command *temp;


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
	// temp->index = 0;
	// temp->cmd_type = FT_CMD_TYPE_SYSTEM;
	// temp->path = "/usr/bin/cat";
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

	temp = (t_command *)malloc(sizeof(t_command));
	temp->comm_len = 3;
	temp->comm_table = (char **)malloc(sizeof(char *) * temp->comm_len);
	temp->comm_table[0] = "ls";
	temp->comm_table[1] = "-lah";
	temp->comm_table[2] = NULL;
	temp->index = 0;
	temp->cmd_type = FT_CMD_TYPE_SYSTEM;
	temp->path = "/usr/bin/ls";
	ft_lstadd_back(cmd_list, ft_lstnew(temp));


	//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! the last line should be executable by execve !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
}

int	executor(char **envp)
{
	pipex(g_access.parser2exec, envp);
	ft_lstclear(&g_access.parser2exec, ft_free_parser);
	return (1);
}


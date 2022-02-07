#include "../incl/minishell.h"


/*
**  @brief Finds and assignes path to searched command name
*/
static int path_finder(char *str, char **cmd_path)
{
	char	*path;
	char	**split;
	char	*temp_path;
	int		i;

	path = getenv("PATH");
	split = ft_split(ft_strchr(path, '/'), ':');
	temp_path = NULL;
	i = 0;
	while (split[i])
	{
		temp_path = ft_strjoin(split[i], ft_strjoin("/", str));
		if (access(temp_path, F_OK) == 0)
		{
			*cmd_path = temp_path;
			ft_free_split(split);
			return (0);
		}
		else if (access(temp_path, F_OK) == -1)
			free((void *)temp_path);
		i++;
	}
	ft_free_split(split);
	return (-1);
}

/*
**  @brief Checks command name and assign command variables properly
*/
static int ft_command_check(char *str, char **cmd_path, int *cmd_type)
{
	int err;

	*cmd_path = NULL;
	if (!ft_strcmp(str, "pwd") || !ft_strcmp(str, "cd") || !ft_strcmp(str, "echo")  || !ft_strcmp(str, "export") || !ft_strcmp(str, "unset") ||
		!ft_strcmp(str, "env") || !ft_strcmp(str, "exit") )
 	{
		*cmd_type = FT_CMD_TYPE_BUILT_IN;
		return (0);
 	}
	else if(!ft_strcmp(str, "<<") || !ft_strcmp(str, "<") || !ft_strcmp(str, ">>") || !ft_strcmp(str, ">"))
	{
		*cmd_type = FT_CMD_TYPE_REDIRECT;
		return (0);
	}
	err = path_finder(str, cmd_path);
	if (err == 0)
		*cmd_type = FT_CMD_TYPE_SYSTEM;
	else if (err == -1)
		*cmd_type = FT_CMD_TYPE_ERROR;
	return (err);
}

/*
**  Use the lex one
*/
static void	ft_free_lex_list(t_list *head)
{
	t_list	*tmp;

	while (head != NULL)
	{
		tmp = head;
		head = head->next;
		free(((t_word *)(tmp->content))->address);
		free(tmp->content);
		free(tmp);
	}
}

/*
** 	Adds new argument to command table
*/
static char** add_to_line(char **line, char *new_str, int *line_len)
{
	char	**new_line;
	int		counter;

	new_line = (char **)malloc(sizeof(char *) * ((*line_len) + 1));
	counter = 0;
	while (counter < *line_len)
	{
		new_line[counter] = line[counter];
		counter++;
	}
	new_line[counter] = new_str;
	(*line_len)++;
	if (line != NULL)
		free(line);
	return new_line;
}

/*
** 	Handles errors
*/
static void error_fun(t_list **list, t_list **lexor_list)
{
	if (FT_PARSER_COMMENT)
		printf("!!!!!!!!!!!!!!!!!!!!!!!PARSER ERROR!!!!!!!!!!!!!!!!!!!!!!!!!!!\n");
	ft_lstclear(list, ft_free_parser);
	ft_free_lex_list(*lexor_list);
	*lexor_list = NULL;
}


static void ft_string_handler(t_list *lex_element, char	***cmd_line, int *cmd_len)
{
	char *str;

	if (ft_strlen(((t_word *)(lex_element->content))->address) != 0)
	{
		str = ft_strdup(((t_word *)(lex_element->content))->address);
		*cmd_line = add_to_line(*cmd_line, str, cmd_len);
	}
}

/*
**  @brief Chechk if string is same as one of redirects
*/
int is_redirect(char *str)
{
	if (!ft_strcmp(str, ">") || !ft_strcmp(str, "<") || !ft_strcmp(str, ">>") || !ft_strcmp(str, "<<"))
		return (1);
	return (0);
}


/*
**  @brief Chechk if string is same as pip
*/
int is_pipe(char *str)
{
	if (!ft_strcmp(str, "|"))
		return (1);
	return (0);
}

int	parser(void)
{
	int		index_counter;
	t_list	*lex_element;
	t_list	*executor_element;
	char	**cmd_line;
	char	**cmd_line_red;
	int		cmd_len;
	t_command	*cmd;
	int return_flag;

	index_counter = 0;
	lex_element = g_access.lexor2parser;
	cmd = NULL;
	return_flag = 0;
	while (1 || return_flag != 0)
	{
		cmd_line = 0;
		cmd_len = 0;
		if (lex_element == NULL || return_flag != 0)
			break;
		while (1 || return_flag != 0)
		{
			if (lex_element == NULL )
				break;
			if (((t_word *)(lex_element->content))->type == FT_SPECIAL_CHAR_STRING)
			{
				if (is_redirect(((t_word *)(lex_element->content))->address))
				{
					cmd_line_red = (char **)ft_calloc(3, sizeof(char *));
					cmd_line_red[0] = ft_strdup(((t_word *)(lex_element->content))->address);
					lex_element = lex_element->next;
					if(lex_element == NULL)
					{
						return_flag = 2;
						g_access.last_return = ft_itoa(2);
						write(2, "bash: syntax error near unexpected token `newline'\n", 51);
						free(cmd_line_red);
						error_fun(&(g_access.parser2exec), &(g_access.lexor2parser));
						break;
					}
					cmd_line_red[1] = ft_strdup(((t_word *)(lex_element->content))->address);
					cmd = (t_command *)malloc(sizeof(t_command));
					cmd->comm_table = cmd_line_red;
					cmd->path = NULL;
					cmd->index = index_counter;
					cmd->comm_len = 3;
					cmd->cmd_type = FT_CMD_TYPE_REDIRECT;
					executor_element = ft_lstnew((void * ) cmd);
					ft_lstadd_back(&(g_access.parser2exec), executor_element);
				}
				else  if (is_pipe(((t_word *)(lex_element->content))->address))
				{
					if (cmd_len == 0)
					{
						return_flag = 2;
						g_access.last_return = ft_itoa(2);
						write(2, "bash: syntax error near unexpected token `|'\n", 45);
						error_fun(&(g_access.parser2exec), &(g_access.lexor2parser));
					}
						else
						lex_element = lex_element->next;
					break ;
				}
				else
				{
					return_flag = 2;
					g_access.last_return = ft_itoa(2);
					write(2, "bash: syntax error near unexpected token'\n", 42);
					error_fun(&(g_access.parser2exec), &(g_access.lexor2parser));
					break ;
				}
			}
			else if (((t_word *)(lex_element->content))->type == FT_STRING)
				ft_string_handler(lex_element, &cmd_line, &cmd_len);
			lex_element = lex_element->next;
		}
		if (return_flag == 0)
		{
			cmd_line = add_to_line(cmd_line, NULL, &cmd_len);
			cmd = (t_command *)malloc(sizeof(t_command));
			cmd->comm_table = cmd_line;
			cmd->path = NULL;
			cmd->index = index_counter;
			cmd->comm_len = cmd_len;
			cmd->cmd_type = 0;
			ft_command_check(cmd->comm_table[0], &cmd->path, &cmd->cmd_type);
			if (FT_PARSER_COMMENT)
				printf("Path if: %s\n", cmd->path);
			executor_element = ft_lstnew((void * ) cmd);
			ft_lstadd_back(&(g_access.parser2exec), executor_element);
			index_counter++;
		}
	}
	if (return_flag == 0)
	{
		ft_free_lex_list(g_access.lexor2parser);
		g_access.lexor2parser = NULL;
	}
	if (FT_PARSER_COMMENT)
		print_list_parse(g_access.parser2exec);
	return (return_flag);
}


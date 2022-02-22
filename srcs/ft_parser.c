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

	if (access(str, F_OK) == 0)
	{
		*cmd_path = ft_strdup(str);
		return (0);
	}
	path = env_value_finder("PATH");
	split = ft_split(ft_strchr(path, '/'), ':');
	temp_path = NULL;
	i = 0;
	if (split != NULL)
	{
		while (split[i])
		{
			temp_path = ft_strjoin_with_scnd_free(split[i], ft_strjoin("/", str));
			if (access(temp_path, F_OK) == 0)
			{
				errno = 0;
				*cmd_path = ft_strdup(temp_path);
				ft_free_split(split);
				if(temp_path != NULL)
					free(temp_path);
				temp_path = NULL;
				return (0);
			}
			else
			{
				if (temp_path != NULL)
					free((void *)temp_path);
				temp_path = NULL;
			}
			i++;
		}
		ft_free_split(split);
	}
	write(2, "minishell: ", 12);
	write(2, str, ft_strlen(str));
	write(2, ": No such file or directory\n", 28);
	if (g_access.last_return != NULL)
		free(g_access.last_return);
	g_access.last_return = ft_itoa(127);
	if(temp_path != NULL)
		free(temp_path);
	return (-1);
}

/**
	@brief Checks command name and assign command type variables properly.
		Also calls function to assign the path of a system execcutables.
	@param str First element of user input.
	@param cmd_path Pointer to command path variable.
	@param cmd_type Pointer to command type flag.
	@return 0 on builtin, system command or redirect and -1 on error type.
*/
static int ft_command_check(char *str, char **cmd_path, int *cmd_type)
{
	int err;
	*cmd_path = NULL; //redundant with callling funtion
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
** 	Adds new argument to command table
*/
static char **add_to_line(char **line, char *new_str, int *line_len)
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
static int	ft_error_handler(t_list **parser_list, t_list **lexor_list, char *msg)
{
	ft_smart_free((void **)&(g_access.last_return));
	g_access.last_return = ft_itoa(2);
	write(2, msg, ft_strlen(msg));
	ft_free_linked_list(parser_list, FT_LIST_TYPE_COMMAND, 1);
	ft_free_linked_list(lexor_list, FT_LIST_TYPE_WORD, 1);
	return (2);
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

/**
	@brief Checks if string is redirect character >, <, << or >>.
	@param str String to be checked.
	@return 1 if redirect character else 0.
*/
int is_redirect(char *str)
{
	if (!ft_strcmp(str, ">") || !ft_strcmp(str, "<") || !ft_strcmp(str, ">>") || !ft_strcmp(str, "<<"))
		return (1);
	return (0);
}


/**
	@brief Checks if string is pipe character |.
	@param str String to be checked.
	@return 1 if pipe character else 0.
*/
int is_pipe(char *str)
{
	if (!ft_strcmp(str, "|"))
		return (1);
	return (0);
}

/**
	@brief Adds new detected command to liked list that will be executed later.
	@param cmd_len Amount of commands.
	@param cmd_line .
	@param index_counter Index of the command in the linked list.
	@return None.
*/
static void	ft_add_command(int cmd_len, char **cmd_line, int index_counter)
{
	t_command	*cmd;
	t_list		*executor_element;

	if(cmd_len > 1)
	{
		cmd = (t_command *)malloc(sizeof(t_command));
		cmd->comm_table = cmd_line;
		cmd->path = NULL;
		cmd->index = index_counter;
		cmd->comm_len = cmd_len;
		cmd->cmd_type = 0;
		ft_command_check(cmd->comm_table[0], &cmd->path, &cmd->cmd_type);
		executor_element = ft_lstnew((void * ) cmd);
		ft_lstadd_back(&(g_access.parser2exec), executor_element);
	}
	else
		ft_free_split(cmd_line);
}

static int	ft_redirection_handler(t_list **lex_element, int *return_flag, int index_counter)
{
	char	**cmd_line_red;

	cmd_line_red = (char **)ft_calloc(3, sizeof(char *));
	cmd_line_red[0] = ft_strdup(((t_word *)((*lex_element)->content))->address);
	*lex_element = (*lex_element)->next;
	if(lex_element == NULL)
	{
		ft_smart_free((void **)&(cmd_line_red[0]));
		free(cmd_line_red);
		*return_flag = ft_error_handler(&(g_access.parser2exec), &(g_access.lexor2parser), "minshell: syntax error near unexpected token `newline'\n");
		return (-1);
	}
	if(((t_word *)((*lex_element)->content))->type == FT_SPECIAL_CHAR_STRING)
	{
		ft_smart_free((void **)&(cmd_line_red[0]));
		free(cmd_line_red);
		*return_flag = ft_error_handler(&(g_access.parser2exec), &(g_access.lexor2parser), "minishell: syntax error near unexpected token'\n");
		return (-1);
	}
	cmd_line_red[1] = ft_strdup(((t_word *)((*lex_element)->content))->address);
	ft_add_command(3, cmd_line_red, index_counter);
	return (0);
}

static int	ft_pipe_handler(t_list **lex_element, int *return_flag, int cmd_len)
{
	if (cmd_len == 0)
		*return_flag = ft_error_handler(&(g_access.parser2exec), &(g_access.lexor2parser), "minishell: syntax error near unexpected token `|'\n");
	else
	{
		*lex_element = (*lex_element)->next;
		if (*lex_element == NULL)
			*return_flag = ft_error_handler(&(g_access.parser2exec), &(g_access.lexor2parser), "minishell: syntax error near unexpected token `|'\n");
	}
	return (-1) ;
}

int	parser(void)
{
	int		index_counter;
	t_list	*lex_element;
	char	**cmd_line;
	int		cmd_len;
	int return_flag;

	index_counter = 0;
	lex_element = g_access.lexor2parser;
	return_flag = 0;
	while (return_flag == 0 && lex_element != NULL)
	{
		cmd_line = 0;
		cmd_len = 0;
		while (return_flag == 0 && lex_element != NULL)
		{
			if (((t_word *)(lex_element->content))->type == FT_SPECIAL_CHAR_STRING)
			{
				if (is_redirect(((t_word *)(lex_element->content))->address))
				{
					if (ft_redirection_handler(&lex_element, &return_flag, index_counter) == -1)
						break ;
				}
				else  if (is_pipe(((t_word *)(lex_element->content))->address))
				{
					if (ft_pipe_handler(&lex_element, &return_flag, cmd_len) == -1)
						break ;
				}
				else
				{
					return_flag = ft_error_handler(&(g_access.parser2exec), &(g_access.lexor2parser), "minishell: syntax error near unexpected token'\n");
					break ;
				}
			}
			else if (((t_word *)(lex_element->content))->type == FT_STRING)
				ft_string_handler(lex_element, &cmd_line, &cmd_len);
			if (cmd_len > PARSER_TABLE_LEN_LIMIT)
			{
				return_flag = ft_error_handler(&(g_access.parser2exec), &(g_access.lexor2parser), "minishell: argument overflow\n");
				break;
			}
			lex_element = lex_element->next;
		}
		cmd_line = add_to_line(cmd_line, NULL, &cmd_len);
		if (return_flag == 0)
		{
			ft_add_command(cmd_len, cmd_line, index_counter);
			index_counter++;
			if (index_counter > PIPE_LIMIT)
				return_flag = ft_error_handler(&(g_access.parser2exec), &(g_access.lexor2parser), "minishell: pipe limit reached\n");
		}
		else
			ft_free_split(cmd_line);
	}
	if (return_flag == 0)
		ft_free_linked_list(&(g_access.lexor2parser),FT_LIST_TYPE_WORD, 1);
	return (return_flag);
}

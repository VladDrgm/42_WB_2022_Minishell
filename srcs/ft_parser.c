#include "../incl/minishell.h"

void    ft_free_split(char **split)
{
    int    i;

    i = 0;
    while (split[i] != NULL)
    {
        free(split[i]);
        i++;
    }
    free(split);
}

char	*ft_strjoin_free(char *s1, char const *s2)
{
	char	*return_s;

	if (!s1 || !s2)
		return (NULL);
	return_s = ft_calloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2)) + 1, 1);
	if (return_s == NULL)
		return (NULL);
	ft_memcpy(return_s, s1, ft_strlen(s1));
	ft_memcpy(return_s + ft_strlen(s1), s2, ft_strlen(s2));
	free (s1);
	return (return_s);
}

int    ft_strcmp(char *s1, char *s2)
{
    int i;

    i = 0;
    while (s1[i] == s2[i] && s1[i] != '\0' && s2[i] != '\0')
        i++;
    return (s1[i] - s2[i]);
}
/*
**	pwd cd echo export unset env exit << < >> >
*/

int ft_command_check(char *str, char **cmd_path)
{
	char	*path;
	char	**split;
	char	*temp_path;
	int		i;

	printf("In check :%s\n", str);
	if (!ft_strcmp(str, "pwd") || !ft_strcmp(str, "cd") || !ft_strcmp(str, "echo")  || !ft_strcmp(str, "export") || !ft_strcmp(str, "unset") ||
		!ft_strcmp(str, "env") || !ft_strcmp(str, "exit") || !ft_strcmp(str, "<<") || !ft_strcmp(str, "<") || !ft_strcmp(str, ">>") || !ft_strcmp(str, ">"))
 	{
 		*cmd_path = 0;
 		return 0;
 	}
	path = getenv("PATH");
	split = ft_split(ft_strchr(path, '/'), ':');
	temp_path = NULL;
	i = 0;
	while (split[i])
	{
		temp_path = ft_strjoin(split[i], ft_strjoin("/", str));
		// printf("PATH: %s\n", temp_path);
		if (access(temp_path, F_OK) == 0)
		{
			*cmd_path = temp_path;
			ft_free_split(split);
			return (0);
		}
		else if (access(temp_path, F_OK) == -1)
		{
			free((void *)temp_path);
			//ft_free_split(split);
			//temp_path = NULL;
			//return (-1);
		}
		i++;
	}
	ft_free_split(split);
	//free((void *)temp_path);
	return (-1);
}


void error_fun(void)
{
	;
}

void	ft_free_lex_list(t_list *head)
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

char** add_to_line(char **line, char *new_str, int *line_len)
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

void	print_element_lex(void *input)
{
	t_word	*word;

	word = (t_word *)input;
	if (word->type == FT_STRING)
		printf("string: %s\n", (char *)(word->address));
	else if (word->type == FT_CHAR)
		printf("char: %c\n", *((char *)(word->address)));
}

/*
**	printslinked list
*/

void	print_list_lex(t_list *el)
{
	ft_lstiter(el, print_element_lex);

}

void ft_comment_check(char ***cmd_table, int *cmd_len)
{
	int i;
	int new_len;
	char **new_line;


	i = 0;
	new_line = NULL;
	new_len = 0;
	// cmd_table++;
	printf("\n________________We are in comment check_____________\n");
	printf("CMD LEN IS : %d\n", *cmd_len);

	while (i < *cmd_len)
	{
		printf("CMD IS %s\n", (*cmd_table)[i]);
		if((*cmd_table)[i][0] == FT_HASHTAG)
		{
			new_len = i;
			break;
		}
		i++;
	}
	if (*cmd_len == i)
		return ;
	i = 0;
	new_line = (char **)malloc (sizeof(char *) * new_len);
	while (i < new_len)
	{
		new_line[i] = ft_strdup((*cmd_table)[i]);
		printf("New Line is %s\n", new_line[i]);
		i++;
	}
	i = 0;
	while (i < *cmd_len)
	{
		free((*cmd_table)[i]);
		i++;
	}
	printf("testing'n\n");
	free(*cmd_table);
	*cmd_table = new_line;
	*cmd_len = new_len;
	int k = 0;
	while (k < new_len)
	{
		printf("While check %s\n", (*cmd_table)[k]);
		k++;
	}

	printf("I is gonna be : %d\n", new_len);


	// char *str = "deki";
	// printf("%s\b\b", str);


}

int	parser(t_list **lex_list, t_list **executor_list)
{
	int		index_counter;
	t_list	*lex_element;
	t_list	*executor_element;
	char	first_redirect;
	char	**cmd_line;
	int		cmd_len;
	char	*str;
	t_command	*cmd;

	index_counter = 0;
	lex_element = *lex_list;
	cmd = NULL;
	first_redirect = 0;
	while (1)
	{
		cmd_line = 0;
		cmd_len = 0;
		if (lex_element == NULL)
			break;
		while (1)
		{	if (lex_element == NULL)
				break;
			if (first_redirect != 0)
			{
				if (((t_word *)(lex_element->content))->type == FT_STRING || *((char *)((t_word *)(lex_element->content))->address) != first_redirect)
				{
					str = (char *)ft_calloc(2, sizeof(char));
					str[0] = first_redirect;
				}
				else
				{
					str = (char *)ft_calloc(3, sizeof(char));
					str[0] = first_redirect;
					str[1] = first_redirect;
					lex_element = lex_element->next;
				}
				cmd_line = add_to_line(cmd_line, str, &cmd_len);
				first_redirect = 0;
			}
			if (((t_word *)(lex_element->content))->type == FT_CHAR)
			{
				if (*((char *)((t_word *)(lex_element->content))->address) == FT_GREATER || *((char *)((t_word *)(lex_element->content))->address) == FT_LESSER || first_redirect != 0)
				{
					if (first_redirect == 0)
					{
						first_redirect = *((char *)((t_word *)(lex_element->content))->address);
						if (cmd_len != 0)
							break;
						if (*((char *)((t_word *)((lex_element->next)->content))->address) == first_redirect)
						{
							str = (char *)ft_calloc(3, sizeof(char));
							str[0] = first_redirect;
							str[1] = first_redirect;
							lex_element = lex_element->next;
						}
						else
						{
							str = (char *)ft_calloc(2, sizeof(char));
							str[0] = first_redirect;
						}
					}
					cmd_line = add_to_line(cmd_line, str, &cmd_len);
					first_redirect = 0;
				}
				if (*((char *)((t_word *)(lex_element->content))->address) == FT_PIPE)
				{
					if (cmd_len == 0)
						error_fun();
					break ;
				}
			}
			if (((t_word *)(lex_element->content))->type == FT_STRING)
			{
				str = (char *)malloc(sizeof(char) * ft_strlen((char *)((t_word *)(lex_element->content))->address) + 1);
				ft_strlcpy(str, (char *)((t_word *)(lex_element->content))->address, ft_strlen((char *)((t_word *)(lex_element->content))->address) + 1);
				cmd_line = add_to_line(cmd_line, str, &cmd_len);
			}
			lex_element = lex_element->next;
		}
		int test_c = 0;
		while(test_c < cmd_len)
		{
			printf("%s\n", cmd_line[test_c]);
			test_c++;
		}
		printf("_______________________\n");
		cmd = (t_command *)malloc(sizeof(t_command));
		cmd->comm_table = cmd_line;
		cmd->path = NULL;
		cmd->index = index_counter;
		ft_command_check(cmd->comm_table[0], &(cmd->path));
		ft_comment_check(&(cmd->comm_table), &cmd_len);
		// printf("PATH in main :%s\n", cmd->path);
		executor_element = ft_lstnew((void * ) cmd);
		ft_lstadd_back(executor_list, executor_element);
		test_c = 0;
		printf("After Comment Check Initialization\n");
		printf("CMD LEN IS %d \n", cmd_len);
		while(test_c < cmd_len)
		{
			printf("%s\n", (cmd->comm_table)[test_c]);
			test_c++;
		}
		// printf("_______________________\n");
		index_counter++;
		if (lex_element == 0)
			break;
		else
			lex_element = lex_element->next;
	}
	ft_free_lex_list(*lex_list);
	return (0);
}


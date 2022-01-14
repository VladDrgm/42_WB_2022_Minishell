#include "../incl/minishell.h"

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

/*
**	pwd cd echo export unset env exit << < >> >
*/

// int ft_command_check(char *str, char *cmd_path)
// {
// 	char	*path;
// 	char	**split;
// 	char	*temp_path;
// 	int		i;

// 	path = getenv("PATH");
// 	split = ft_split(ft_strchr(path, '/'), ':');
// 	temp_path = NULL;
// 	i = 0;
// 	while (split[i])
// 	{
// 		if (split[i] == "pwd" || split[i] == "cd" || split[i] == "echo"  || split[i] == "export" || split[i] == "unset" ||
// 			split[i] == "env" || split[i] == "exit" || split[i] == "<<" || split[i] == "<" || split[i] == ">>" || split[i] == ">")
// 		{
// 			free(path);
// 			ft_free_split(split);
// 			*cmd_path = 0;
// 			return 0;
// 		}
// 		temp_path = ft_strjoin_free(split[i], ft_strjoin("/", str));
// 		if (access(temp_path, F_OK) == 0)
// 		{
// 			*cmd_path = temp_path;
// 			ft_free_split(split);
// 			free(path);
// 			return (0);
// 		}
// 		else if (access(temp_path, F_OK) == -1)
// 		{
// 			free((void *)temp_path);
// 			ft_free_split(split);
// 			free(path);
// 			temp_path = NULL;
// 			return (-1);
// 		}
// 		i++;
// 	}
// 	ft_free_split(split);
// 	free(path);
// 	return (0);
// }

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

int	parser(t_list **lex_list, t_list **executor_list)
{
	print_list_lex(*lex_list);
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
	while (1)
	{
		cmd_line = 0;
		cmd_len = 0;
		if (lex_element == 0)
			break;
		while (1)
		{		
			if (lex_element == 0)
				break;
			if (((t_word *)(lex_element->content))->type == FT_CHAR)
			{
				if (*((char *)((t_word *)(lex_element->content))->address) == FT_GREATER || *((char *)((t_word *)(lex_element->content))->address) == FT_LESSER)
				{
					first_redirect = *((char *)((t_word *)(lex_element->content))->address);
					lex_element = lex_element->next;
					if (((t_word *)(lex_element->content))->type == FT_CHAR && *((char *)((t_word *)(lex_element->content))->address) == first_redirect)
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
					cmd_line = add_to_line(cmd_line, str, &cmd_len);
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
		executor_element = ft_lstnew((void * ) cmd);
		ft_lstadd_back(executor_list, executor_element);
		index_counter++;
		if (lex_element == 0)
			break;
		else
			lex_element = lex_element->next;
	}
	ft_free_lex_list(*lex_list);
	return (0);
}

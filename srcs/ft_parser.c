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

void	print_element_parser(void *input)
{
	t_command	*cmd;
	int 		test_c;

	cmd = (t_command *)input;
	test_c = 0;
	// printf("Len is %d\n", cmd->comm_len);
	while(test_c < (cmd->comm_len))
	{
		// printf("1\n");
		printf("%s\n", cmd->comm_table[test_c]);
		// printf("Len is %d\n", cmd->comm_len);
		// printf("2\n");
		test_c++;
	}
	printf("*****************************************************\n");
}

/*
**	printslinked list
*/

void	print_list_parse(t_list *el)
{
	ft_lstiter(el, print_element_parser);
}

// void ft_comment_check(char ***cmd_table, int *cmd_len)
// {
// 	int i;
// 	int new_len;
// 	char **new_line;

// 	i = 0;
// 	new_line = NULL;
// 	new_len = 0;
// 	while (i < *cmd_len)
// 	{
// 		if((*cmd_table)[i][0] == FT_HASHTAG)
// 		{
// 			new_len = i;
// 			break;
// 		}
// 		i++;
// 	}
// 	if (*cmd_len == i)
// 		return ;
// 	i = 0;
// 	new_line = (char **)malloc (sizeof(char *) * new_len);
// 	while (i < new_len)
// 	{
// 		new_line[i] = ft_strdup((*cmd_table)[i]);
// 		i++;
// 	}
// 	i = 0;
// 	while (i < *cmd_len)
// 	{
// 		free((*cmd_table)[i]);
// 		i++;
// 	}
// 	free(*cmd_table);
// 	*cmd_table = new_line;
// 	*cmd_len = new_len;
// }

void ft_free_parser(void *parser)
{
	int i;
	t_command *cmd;

	i = 0;
	cmd = (t_command *)parser;
    while (i < cmd->comm_len)
    {
        free(cmd->comm_table[i]);
        i++;
    }
	free(cmd->comm_table);
	free(parser);
}

void error_fun(t_list **list, t_list **lexor_list)
{
	ft_lstclear(list, ft_free_parser);
	ft_free_lex_list(*lexor_list);
	*lexor_list = NULL;
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
						error_fun(executor_list, lex_list);
					break ;
				}
			}
			if (((t_word *)(lex_element->content))->type == FT_STRING)
			{
				if (ft_strlen((char *)((t_word *)(lex_element->content))->address) != 0)
				{
					str = (char *)malloc(sizeof(char) * ft_strlen((char *)((t_word *)(lex_element->content))->address) + 1);
					ft_strlcpy(str, (char *)((t_word *)(lex_element->content))->address, ft_strlen((char *)((t_word *)(lex_element->content))->address) + 1);
					cmd_line = add_to_line(cmd_line, str, &cmd_len);
				}
			}
			lex_element = lex_element->next;
		}
		cmd = (t_command *)malloc(sizeof(t_command));
		cmd->comm_table = cmd_line;
		cmd->path = NULL;
		cmd->index = index_counter;
		cmd->comm_len = cmd_len;
		//ft_comment_check(&(cmd->comm_table), &cmd->comm_len);
		executor_element = ft_lstnew((void * ) cmd);
		ft_lstadd_back(executor_list, executor_element);
		index_counter++;
		if (lex_element == 0)
			break;
		else
			lex_element = lex_element->next;
	}
	ft_free_lex_list(*lex_list);
	*lex_list = NULL;
	if (FT_PARSER_COMMENT)
		print_list_parse(*executor_list);
	return (0);
}


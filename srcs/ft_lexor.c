#include "../incl/minishell.h"

void	ft_free_list(t_list *head)
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

void	print_element(void *input)
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

void	print_list(t_list *el)
{
	ft_lstiter(el, print_element);
}

/*
**	adds substring to linked list
*/

void	add_substring(t_list **list, int end, char *str)
{
	char	*sub_str;
	t_word	*word;
	t_list	*new_el;

	if (end <= 0)
		return ;
	sub_str = ft_substr(str, 0, end);
	word = (t_word *)malloc(sizeof(t_word));
	word->type = FT_STRING;
	word->address = (void *)sub_str;
	new_el = ft_lstnew((void *)word);
	ft_lstadd_back(list, new_el);
}

/*
** adds special char to linked list
*/

void	add_specialchar(t_list **list, char ch)
{
	char	*cp;
	t_word	*word;
	t_list	*new_el;

	cp = (char *)malloc(sizeof(char));
	*cp = ch;
	word = (t_word *)malloc(sizeof(t_word));
	word->type = FT_CHAR;
	word->address = (void *)cp;
	new_el = ft_lstnew((void *)word);
	ft_lstadd_back(list, new_el);
}

/*
**	handels sigle quotes
*/

int	single_q_handler(t_list **list, char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == FT_SINGLE_QUOTE)
		{
			add_substring(list, i, str);
			add_specialchar(list, FT_SINGLE_QUOTE);
			return (i);
		}
		i++;
	}
	return (-1);
}

/*
**	handels double quotes
*/

int	double_q_handler(t_list **list, char *str)
{
	int	i;
	int	beginning;
	int env;

	i = 0;
	env = 0;
	beginning = 0;
	while (str[i] != '\0')
	{
		if (str[i] == FT_DOUBLE_QUOTE)
		{
			add_substring(list, i - beginning, &(str[beginning]));
			return (i);
		}
		else if (str[i] == FT_DOLLAR_SIGN)
		{
			add_substring(list, i - beginning, &(str[beginning]));
			beginning = i;
			env = 1;
		}
		else if (str[i] == FT_SPACE && env == 1)
		{
			add_substring(list, i - beginning, &(str[beginning]));
			beginning = i;
			env = 0;
		}
		i++;
	}
	return (-1);
}

/*
**	clean up function
*/

void	errorfun(void)
{
	//to be implemented
	;
}

/*
**	Implemnted
**	''
**	""
**	#
**	|
**	[SPACE]
**	-
**	<
**	>
**	<<
**	>>
**	Every
*/

/*
**	element beforehand
**	if double quoute, single quote,
**	if space == thats a comment
**	if redirect
**	if pipe
*/

void ft_comment_check(char **args)
{
	int i;
	int s_quote_flag;
	int d_quote_flag;
	char *temp;

	i = 0;
	s_quote_flag = 0;
	d_quote_flag = 0;
	while ((*args)[i])
	{
		if ((*args)[i] == FT_SINGLE_QUOTE)
			s_quote_flag++;
		if ((*args)[i] == FT_DOUBLE_QUOTE)
			d_quote_flag++;
		if ((*args)[i] == FT_HASHTAG)
		{
			if (i == 0)
				break;
			if (s_quote_flag % 2 == 0 && d_quote_flag % 2 == 0)
				if ((*args)[i - 1] == FT_SPACE || (*args)[i - 1] == FT_PIPE || (*args)[i - 1] == FT_LESSER || (*args)[i - 1] == FT_GREATER)
					break;
		}
		i++;
	}
	temp = ft_substr(*args, 0, i);
	free(*args);
	*args = temp;

	// (*args)[i] = '\0';
}

int	lexor(t_list **list, char *args)
{
	int		i;
	int		begining;
	char	last;
	int		flag;


	i = 0;
	begining = 0;
	last = FT_SPACE;
	flag = 0;
	if (FT_LEXOR_COMMENT)
		printf("\n***********BEFORE COMMENT CHECK********** \n%s\n and the length is %ld", args, ft_strlen(args));
	ft_comment_check(&args);
	if (FT_LEXOR_COMMENT)
		printf("\n************AFTER COMMENT CHECK********** \n%s\n and the length is %ld", args, ft_strlen(args));
	//env check
	//command check
	while (args[i] != '\0')
	{
		if (last == FT_SPACE && args[i] != FT_SPACE)
		{
			begining = i;
		}
		else if (last != FT_SPACE && args[i] == FT_SPACE)
		{
			add_substring(list, i - begining, &(args[begining]));
		}
		if (args[i] == FT_PIPE || args[i] == FT_GREATER || \
			args[i] == FT_LESSER)
		{
			add_substring(list, i - begining, &(args[begining]));
			add_specialchar(list, args[i]);
			begining = i + 1;
		}
		else if (args[i] == FT_DOLLAR_SIGN)
		{
			add_substring(list, i - begining, &(args[begining]));
			begining = i;
		}
		if (args[i] == FT_SINGLE_QUOTE)
		{
			add_substring(list, i - begining, &(args[begining]));
			flag = single_q_handler(list, &(args[i + 1]));
			if (flag == -1)
			{
				errorfun();
				printf("Unfinsihed single quote\n");
				break;
			}
			i = i + flag + 1;
			begining = i + 1;
		}
		if (args[i] == FT_DOUBLE_QUOTE)
		{
			add_substring(list, i - begining, &(args[begining]));
			flag = double_q_handler(list, &(args[i + 1]));
			if (flag == -1)
			{
				errorfun();
				printf("Unfinsihed double quote\n");
				break;
			}
			i = i + flag + 1; //we move counter I to the next letter from the next quote
			begining = i + 1; // begining of the next word should be after the first quote
		}
		last = args[i];
		i++;
	}
	if(args[i - 1] != FT_SPACE && i > 0)
		add_substring(list, i - begining, &(args[begining]));
	if (FT_LEXOR_COMMENT)
	{
		printf("We are in lexor %s\n", args);
		print_list(*list);
		printf("Flag is %d\n", flag);
	}
	if (flag == -1)
		ft_free_list(*list);
	free(args);
	return flag;
}
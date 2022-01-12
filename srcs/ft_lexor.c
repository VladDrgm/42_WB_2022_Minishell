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
	// free(word);
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
	// free(cp);
	// free(word);
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

	i = 0;
	beginning = 0;
	while (str[i] != '\0')
	{
		if (str[i] == FT_DOUBLE_QUOTE)
		{
			add_substring(list, i - beginning, &(str[beginning]));
			add_specialchar(list, FT_DOUBLE_QUOTE);
			return (i);
		}
		else if (str[i] == FT_DOLLAR_SIGN)
		{
			add_substring(list, i - beginning, &(str[beginning]));
			add_specialchar(list, FT_DOLLAR_SIGN);
			beginning = i + 1;
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

int	lexor(t_list **list, char *args)
{
	int		i;
	int		begining;
	char	last;
	int		flag;

	i = 0;
	begining = 0;
	last = FT_SPACE;
	while (args[i] != '\0')
	{
		if (last == FT_SPACE && args[i] != FT_SPACE)
		{
			begining = i;
			if (args[i] == FT_MINUS || args[i] == FT_HASHTAG)
			{
				add_specialchar(list, args[i]);
				begining++;
			}
		}
		else if (last != FT_SPACE && args[i] == FT_SPACE)
		{
			add_substring(list, i - begining, &(args[begining]));
			add_specialchar(list, FT_SPACE);
		}
		if (args[i] == FT_PIPE || args[i] == FT_GREATER || \
			args[i] == FT_LESSER || args[i] == FT_DOLLAR_SIGN)
		{
			add_substring(list, i - begining, &(args[begining]));
			add_specialchar(list, args[i]);
			begining = i + 1;
		}
		if (args[i] == FT_SINGLE_QUOTE)
		{
			add_substring(list, i - begining, &(args[begining]));
			add_specialchar(list, FT_SINGLE_QUOTE);
			flag = single_q_handler(list, &(args[i + 1]));
			if (flag == -1)
			{
				errorfun();
				printf("Unfinsihed single quote\n");
				break;
				// return (-1); //here the function was working
			}

			i = i + flag + 1;
			begining = i + 1;

		}
		if (args[i] == FT_DOUBLE_QUOTE)
		{
			add_substring(list, i - begining, &(args[begining]));
			add_specialchar(list, FT_DOUBLE_QUOTE);
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
	add_substring(list, i - begining, &(args[begining]));
	print_list(*list);
	printf("We are in lexor %s\n", args);
	printf("Flag is %d\n", flag);
	if (flag == -1)
	{
		// printf("Clean the list\n");
		// free(args);
		ft_free_list(*list);
	}
	return flag;
}

//add flags
//free "exit"
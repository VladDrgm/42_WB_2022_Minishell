#include "../incl/minishell.h"

/*
**	@brief Generic function for freeing linked lists
**	@param t_list **list . Function used for cleaning the linked lists and its content.
**	@return /
**	@todo /
*/

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

/*
**	@brief Adding Special Characters to a linked list
**	@param t_list **list, char c.
**	@return /
**	@todo /
*/

void	add_specialchar_string(t_list **list, char *str)
{
	char	*cp;
	t_word	*word;
	t_list	*new_el;

	word = (t_word *)malloc(sizeof(t_word));
	word->type = FT_CHAR;
	word->address = ft_strdup(str);
	new_el = ft_lstnew((void *)word);
	ft_lstadd_back(list, new_el);
}

/*
**	@brief Function used for handling single and double quotes from the read_line input
**	@param char *str, char **current_str, char q_char. q_char variable represents Single or Double Quote
**	@return on success command returns positive integer, on failuler it returns -1.
**	@todo /
*/

int	q_handler(char *str, char **current_str, char q_char)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == q_char)
		{
			if (FT_LEXOR_COMMENT)
				printf("at 6-> begin: %d, i:%d, args: %s\n", 0, i , str);
			*current_str = join2current_str(*current_str, ft_substr(str, 0, i));
			return (i);
		}
		i++;
	}
	return (-1);
}

/*
**	@brief Function implemented on possible error places.
**	@param /
**	@return /
**	@todo Include this function for error handling in lexor.
*/

void	errorfun(void)
{
	//to be implemented
	;
}
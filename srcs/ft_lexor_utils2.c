/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lexor_utils2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamuller <mamuller@student.42wolfsburg>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 21:17:43 by mamuller          #+#    #+#             */
/*   Updated: 2022/02/22 11:05:21 by mamuller         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/minishell.h"

/**
	@brief Adds new node with input string and special char string type to 
			lexor2parser linked list.
	@param list Linked list to be expanded.
	@param str String to be added to the content of a liked
			list node.
	@return None.
*/
void	add_specialchar_string(t_list **list, char *str)
{
	t_word	*word;
	t_list	*new_el;

	word = (t_word *)malloc(sizeof(t_word));
	word->type = FT_SPECIAL_CHAR_STRING;
	word->address = ft_strdup(str);
	new_el = ft_lstnew((void *)word);
	ft_lstadd_back(list, new_el);
}

/**
	@brief Handles adding characters to current string in case of 
			opened single or double quote.
	@param str String from the starting of the opening quote.
			Doesnt contain opening quote.
	@param current_str Pointer to substring of users input that is 
	 		analyzed in this call.
	@param q_char Type of quote character (single or double).
	@return On success number of added characters -1 else -1.
*/
int	q_handler(char *str, char **current_str, char q_char)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == q_char)
		{
			*current_str = join2current_str(*current_str, ft_substr(str, 0, i));
			return (i);
		}
		i++;
	}
	return (-1);
}

/**
	@brief Checks if char is quote and increases the counter values
		of calling function.
	@param c Character to be checked.
	@param s_quote_flag Pointer to a counter for single quotes.
	@param d_quote_flag Pointer to a counter for double quotes.
	@return None.
*/
static void	ft_quote_counter(char c, int *s_quote_flag, int *d_quote_flag)
{
	if (c == FT_SINGLE_QUOTE)
		(*s_quote_flag)++;
	if (c == FT_DOUBLE_QUOTE)
		(*d_quote_flag)++;
}

/**
	@brief Checks for comments (#) in user input and removes them 
		by changing input string.
	@param args Pointer to a string to be checked for comments.
	@return None.
*/
void	ft_comment_check(char **args)
{
	int		i;
	int		s_quote_flag;
	int		d_quote_flag;
	char	*temp;

	i = 0;
	s_quote_flag = 0;
	d_quote_flag = 0;
	while ((*args)[i])
	{
		ft_quote_counter((*args)[i], &s_quote_flag, &d_quote_flag);
		if ((*args)[i] == FT_HASHTAG)
		{
			if (i == 0)
				break ;
			if (s_quote_flag % 2 == 0 && d_quote_flag % 2 == 0)
				if ((*args)[i - 1] == FT_SPACE || (*args)[i - 1] == FT_PIPE \
				|| (*args)[i - 1] == FT_LESSER || (*args)[i - 1] == FT_GREATER)
					break ;
		}
		i++;
	}
	temp = ft_substr(*args, 0, i);
	free(*args);
	*args = temp;
}

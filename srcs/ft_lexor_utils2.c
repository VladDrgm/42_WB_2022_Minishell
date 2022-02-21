/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lexor_utils2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamuller <mamuller@student.42wolfsburg>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 21:17:43 by mamuller          #+#    #+#             */
/*   Updated: 2022/02/21 21:17:48 by mamuller         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/minishell.h"

/*
**	@brief Adding Special Characters to a linked list
**	@param t_list **list, char c.
**	@return /
**	@todo /
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

/*
**	@brief Function used for handling single and double quotes
	from the read_line input
**	@param char *str, char **current_str, char q_char. q_char variable 
	represents Single or Double Quote
**	@return on success command returns positive integer, 
	on failuler it returns -1.
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
			*current_str = join2current_str(*current_str, ft_substr(str, 0, i));
			return (i);
		}
		i++;
	}
	return (-1);
}

static void	ft_quote_counter(char c, int *s_quote_flag, int *d_quote_flag)
{
	if (c == FT_SINGLE_QUOTE)
		(*s_quote_flag)++;
	if (c == FT_DOUBLE_QUOTE)
		(*d_quote_flag)++;
}

/*
**	@brief Function used for comment check from standard input
**	@param char **args. If args containes # everything afterwards is being removed
**	@return No Return Value.
**	@todo /
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

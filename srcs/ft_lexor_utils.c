/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lexor_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamuller <mamuller@student.42wolfsburg>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 21:06:42 by mamuller          #+#    #+#             */
/*   Updated: 2022/02/22 11:04:11 by mamuller         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/minishell.h"

/**
	@brief Concatenates one string to another.
	@param current_str, Pointer to substring of users input that is 
	 		analyzed in this call.
	@param add_on String being appened to a current string.
	@return Pointer to extended string.
	@exception Returns a duplicate of the second string in case
			the first string is NULL.
*/
char	*join2current_str(char *current_str, char *add_on)
{
	char	*temp;

	if (current_str)
		temp = ft_strjoin(current_str, add_on);
	else
		temp = ft_strdup(add_on);
	ft_smart_free((void **)&current_str);
	ft_smart_free((void **)&add_on);
	return (temp);
}

/**
	@brief Adds new node with input string and string type to 
			lexor2parser linked list.
	@param list Linked list to be expanded.
	@param str String to be added to the content of a liked
			list node.
	@return None.
*/
void	add_string(t_list **list, char	*str)
{
	t_word	*word;
	t_list	*new_el;

	if (str == NULL)
		return ;
	word = (t_word *)malloc(sizeof(t_word));
	word->type = FT_STRING;
	word->address = ft_strdup(str);
	new_el = ft_lstnew((void *)word);
	ft_lstadd_back(list, new_el);
}

/**
	@brief Checks if char is space.
	@param ch Character to be checked.
	@return 1 if space else 0.
*/
int	is_space(char ch)
{
	if (ch == FT_SPACE)
		return (1);
	return (0);
}

/**
	@brief Checks if char is |, > or <.
	@param ch Character to be checked.
	@return 1 if special char else 0.
*/
int	is_special_char(char ch)
{
	if (ch == FT_PIPE || ch == FT_GREATER || ch == FT_LESSER)
		return (1);
	return (0);
}

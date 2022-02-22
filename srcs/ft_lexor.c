/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lexor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamuller <mamuller@student.42wolfsburg>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 20:46:18 by mamuller          #+#    #+#             */
/*   Updated: 2022/02/21 20:46:18 by mamuller         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/minishell.h"

/**
	 @brief Checks for single and double quotes.
	 @param current_str Pointer to substring of users input that is 
	 		analyzed in this call.
	 @param args String of users input.
	 @param strt Pointer to starting index of the current string.
	 @param i Pointer to current character.
	 @return None.
 */
static int	ft_check_qu(char **current_str, char *args, int *begining, int *i)
{
	int	flag;

	flag = 0;
	if (args[*i] == FT_SINGLE_QUOTE)
	{
		flag = ft_lex_single_quote_handler(current_str, args, *begining, *i);
		if (flag == -1)
			return (flag);
		*i = *i + flag + 1;
		*begining = *i + 1;
	}
	else if (args[*i] == FT_DOUBLE_QUOTE)
	{
		flag = ft_lex_double_quote_handler(current_str, args, *begining, *i);
		if (flag == -1)
			return (flag);
		*i = *i + flag + 1;
		*begining = *i + 1;
	}
	return (flag);
}

/**
	 @brief Checks for special character in a string like space, >, < and |.
	 @param current_str Pointer to substring of users input that is 
	 		analyzed in this call.
	 @param args String of users input.
	 @param strt Pointer to starting index of the current string.
	 @param i Pointer to current character.
	 @return None.
 */
static void	ft_check_sp_char(char **current_str, char *args, int *strt, int *i)
{
	char	last;

	if (*i == 0)
		last = FT_SPACE;
	else
		last = args[*i - 1];
	if ((is_space(last) && !is_space(args[*i])))
		*strt = *i;
	else if (!is_special_char(last) && is_special_char(args[*i]))
	{
		ft_lex_space_handler(current_str, args, *strt, *i);
		*strt = *i;
	}
	else if (is_special_char(last) && !is_special_char(args[*i]))
	{
		ft_lex_operand_handler(current_str, args, *strt, *i);
		*strt = *i;
	}
	else if ((!is_space(last) && is_space(args[*i])))
	{
		ft_lex_space_handler(current_str, args, *strt, *i);
		*strt = *i;
	}
}

/**
	 @brief Checks if input contains only spaces.
	 @param flag Pointer to error flag sets error flag in calling function.
	 @return None.
 */
static void	ft_check_empty_input(int *flag)
{
	if (ft_lstsize(g_access.lexor2parser) == 0 && *flag == 0)
	{
		ft_free_linked_list(&g_access.lexor2parser, FT_LIST_TYPE_WORD, 1);
		*flag = -1;
	}
}

/**
	 @brief Processing string readline to lexor into a linked list
	 		to be used by parser.
	 @return Error flag. -1 on error else 0.
	 @exception Removes comments.
	 @exception Handles env variables ($).
 */
int	lexor(void)
{
	int		i;
	int		start;
	int		flag;
	char	*current_str;

	i = 0;
	start = 0;
	flag = 0;
	ft_comment_check(&g_access.read_line2lexor);
	ft_env_check(&g_access.read_line2lexor);
	current_str = NULL;
	while (g_access.read_line2lexor[i] != '\0')
	{
		ft_check_sp_char(&current_str, g_access.read_line2lexor, &start, &i);
		flag = ft_check_qu(&current_str, g_access.read_line2lexor, &start, &i);
		i++;
	}
	if (flag == -1)
		ft_free_linked_list(&g_access.lexor2parser, FT_LIST_TYPE_WORD, 1);
	else if (!is_space(g_access.read_line2lexor[i - 1]) && i > 0)
		ft_lex_string_reminder_handler(&current_str, \
			g_access.read_line2lexor, start, i);
	ft_smart_free((void **)&g_access.read_line2lexor);
	ft_check_empty_input(&flag);
	return (flag);
}

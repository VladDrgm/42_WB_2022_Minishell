/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lexor_handlers.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamuller <mamuller@student.42wolfsburg>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/22 11:10:40 by mamuller          #+#    #+#             */
/*   Updated: 2022/02/22 11:33:04 by mamuller         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/minishell.h"

/**
	 @brief Handling of substring.
	 @param current_str Pointer to substring of users input that is 
	 		analyzed in this call.
	 @param args String of users input.
	 @param begining Start index of the current string.
	 @param i End index of the current string.
	 @return None.
 */
void	ft_lex_space_handler(char **current_str, char *args, \
	int begining, int i)
{
	*current_str = join2current_str(*current_str, \
		ft_substr(args, begining, i - begining));
	if (ft_strlen(*current_str))
		add_string(&(g_access.lexor2parser), *current_str);
	ft_smart_free((void **)current_str);
}

/**
	 @brief Handling of substring of special characters like |, >, and <.
	 @param current_str Pointer to substring of users input that is 
	 		analyzed in this call.
	 @param args String of users input.
	 @param begining Start index of the current string.
	 @param i End index of the current string.
	 @return None.
 */
void	ft_lex_operand_handler(char **current_str, char *args, \
	int begining, int i)
{
	*current_str = join2current_str(*current_str, \
		ft_substr(args, begining, i - begining));
	if (ft_strlen(*current_str))
		add_specialchar_string(&(g_access.lexor2parser), *current_str);
	ft_smart_free((void **)current_str);
}

/**
	 @brief Handles single quotes by joining substring to current string,
	 		calling respective quote handler and handling resulting errors.
	 @param current_str Pointer to substring of users input that is 
	 		analyzed in this call.
	 @param args String of users input.
	 @param begining Start index of the current string.
	 @param i End index of the current string.
	 @return On success number of added characters -1 else -1.
 */
int	ft_lex_single_quote_handler(char **current_str, char *args, \
	int begining, int i)
{
	int	flag;

	flag = 0;
	*current_str = join2current_str(*current_str, \
		ft_substr(args, begining, i - begining));
	flag = q_handler(&(args[i + 1]), current_str, FT_SINGLE_QUOTE);
	if (flag == -1)
	{
		free(*current_str);
		*current_str = NULL;
		printf("minishe11: Unfinished single quote\n");
		if (g_access.last_return != NULL)
			free(g_access.last_return);
		g_access.last_return = ft_itoa(3);
		return (flag);
	}
	return (flag);
}

/**
	 @brief Handles double quotes by joining substring to current string,
	 		calling respective quote handler and handling resulting errors.
	 @param current_str Pointer to substring of users input that is 
	 		analyzed in this call.
	 @param args String of users input.
	 @param begining Start index of the current string.
	 @param i End index of the current string.
	 @return On success number of added characters -1 else -1.
 */
int	ft_lex_double_quote_handler(char **current_str, char *args, \
	int begining, int i)
{
	int	flag;

	flag = 0;
	*current_str = join2current_str(*current_str, \
		ft_substr(args, begining, i - begining));
	flag = q_handler(&(args[i + 1]), current_str, FT_DOUBLE_QUOTE);
	if (flag == -1)
	{
		free(*current_str);
		*current_str = NULL;
		printf("minishe11: Unfinished double quote\n");
		if (g_access.last_return != NULL)
			free(g_access.last_return);
		g_access.last_return = ft_itoa(3);
		return (flag);
	}
	return (flag);
}

/**
	 @brief Handling rest of the string at the end of the input.
	 @param current_str Pointer to substring of users input that is 
	 		analyzed in this call.
	 @param args String of users input.
	 @param begining Start index of the current string.
	 @param i End index of the current string.
	 @return None.
 */
void	ft_lex_string_reminder_handler(char **current_str, char *args, \
	int begining, int i)
{
	*current_str = join2current_str(*current_str, \
		ft_substr(args, begining, i - begining));
	if (ft_strlen(*current_str))
	{
		if (is_special_char(args[begining]))
			add_specialchar_string(&(g_access.lexor2parser), *current_str);
		else
			add_string(&(g_access.lexor2parser), *current_str);
	}
	ft_smart_free((void **)current_str);
}

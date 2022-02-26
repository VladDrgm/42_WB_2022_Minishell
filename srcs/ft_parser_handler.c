/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parser_handler.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamuller <mamuller@student.42wolfsburg>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/22 21:57:51 by mamuller          #+#    #+#             */
/*   Updated: 2022/02/27 15:00:05 by mamuller         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/minishell.h"

/**
	@brief Handles special character for redirections and their filenames
		and prints redirection errors (unexpected token or unexpected NL).
	@param lex_element Pointer to the current element of the lexor.
	@param return_flag Pointer to return flag.
	@param index_counter Index counter value.
	@return 0 on sucess else -1 (on error).
	@exception If the special character indicates heredoc (<<), then 
		we get stop word.
*/
static int	ft_redirection_handler(t_list **lex_element, \
	int *return_flag, int index_counter)
{
	char	**cmd_line_red;

	cmd_line_red = (char **)ft_calloc(3, sizeof(char *));
	cmd_line_red[0] = ft_strdup(((t_word *)((*lex_element)->content))->address);
	*lex_element = (*lex_element)->next;
	if (*lex_element == NULL)
	{
		ft_smart_free((void **)&(cmd_line_red[0]));
		free(cmd_line_red);
		*return_flag = ft_parser_error_handler(&(g_access.parser2exec), \
			&(g_access.lexor2parser), FT_ERR_PR_TK_NL);
		return (-1);
	}
	if (((t_word *)((*lex_element)->content))->type == FT_SPECIAL_CHAR_STRING)
	{
		ft_smart_free((void **)&(cmd_line_red[0]));
		free(cmd_line_red);
		*return_flag = ft_parser_error_handler(&(g_access.parser2exec), \
			&(g_access.lexor2parser), FT_ERR_PR_TK);
		return (-1);
	}
	cmd_line_red[1] = ft_strdup(((t_word *)((*lex_element)->content))->address);
	ft_add_command(3, cmd_line_red, index_counter);
	return (0);
}

/**
	@brief Handles special character pipe and it's errors (pipe in first place
		or last place). 
	@param lex_element Pointer to the current element of the lexor.
	@param return_flag Pointer to return flag.
	@param cmd_len Command length value.
	@return None.
*/
static void	ft_pipe_handler(t_list **lex_element, int *return_flag, int cmd_len)
{
	if (cmd_len == 0)
		*return_flag = ft_parser_error_handler(&(g_access.parser2exec), \
			&(g_access.lexor2parser), FT_ERR_PR_TK_PIPE);
	else
	{
		*lex_element = (*lex_element)->next;
		if (*lex_element == NULL)
			*return_flag = ft_parser_error_handler(&(g_access.parser2exec), \
				&(g_access.lexor2parser), FT_ERR_PR_TK_PIPE);
	}
}

/**
	@brief Checks for allowed special characters and redirects to 
		respective handlers. 
	@param lex_element Pointer to the current element of the lexor.
	@param return_flag Pointer to return flag.
	@param cmd_len Pointer to command length value.
	@param index_counter Index counter value.
	@return 1 on properly handles special character else 0.
	@exception In case of unallowed special character
		an error message is printed and 1 is returned.
*/
static int	ft_special_char_string_handler(t_list **lex_element, \
	int *return_flag, int cmd_len, int index_counter)
{
	if (is_redirect(((t_word *)((*lex_element)->content))->address))
	{
		if (ft_redirection_handler(lex_element, return_flag, \
			index_counter) == -1)
			return (1);
	}
	else if (is_pipe(((t_word *)((*lex_element)->content))->address))
	{
		ft_pipe_handler(lex_element, return_flag, cmd_len);
		return (1);
	}
	else
	{
		*return_flag = ft_parser_error_handler(&(g_access.parser2exec), \
			&(g_access.lexor2parser), FT_ERR_PR_TK);
		return (1);
	}
	return (0);
}

/**
	@brief Handles adding normal strings (command names and arguments)
		to cmd_line.
	@param lex_element Pointer to the current element of the lexor.
	@param cmd_line Pointer to command line array.
	@param cmd_len Pointer to command length value.
	@return None.
*/
static void	ft_normal_char_string_handler(t_list *lex_element, \
	char	***cmd_line, int *cmd_len)
{
	char	*str;

	if (ft_strlen(((t_word *)(lex_element->content))->address) != 0)
	{
		str = ft_strdup(((t_word *)(lex_element->content))->address);
		*cmd_line = add_to_line(*cmd_line, str, cmd_len);
	}
}

/**
	@brief Handles all passed strings from lexor and redirects them 
		to respective sub-handler.
	@param lex_element Pointer to the current element of the lexor.
	@param cmd_line Pointer to command line array.
	@param cmd_len Pointer to command length value.
	@param index_counter Pointer to the index counter.
	@return Returns error flag. 
		0 on normal execution, 1 for break and 2 || 3 for error.
	@exception Handles parser argument overflow.
*/
int	ft_parser_string_handler(t_list **lex_element, \
	char ***cmd_line, int *cmd_len, int index_counter)
{
	int	return_flag;

	return_flag = 0;
	if (((t_word *)((*lex_element)->content))->type == FT_SPECIAL_CHAR_STRING)
	{
		if (ft_special_char_string_handler(lex_element, &return_flag, \
			*cmd_len, index_counter))
			return (return_flag + 1);
	}
	else if (((t_word *)((*lex_element)->content))->type == FT_STRING)
		ft_normal_char_string_handler(*lex_element, cmd_line, cmd_len);
	if (*cmd_len > PARSER_TABLE_LEN_LIMIT)
	{
		return_flag = ft_parser_error_handler(&(g_access.parser2exec), \
			&(g_access.lexor2parser), FT_ERROR_PARSER_ARG_OVERFLOW);
		return (return_flag);
	}
	return (return_flag);
}

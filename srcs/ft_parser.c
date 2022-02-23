/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamuller <mamuller@student.42wolfsburg>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/22 21:57:05 by mamuller          #+#    #+#             */
/*   Updated: 2022/02/23 11:39:56 by mamuller         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/minishell.h"

/**
	@brief Adds new detected command to liked list that will be executed later.
	@param cmd_len Command length value.
	@param cmd_line Command line array.
	@param index_counter Pointer to the index counter.
	@return None.
	@exception If line is too short then command line is freed.
*/
void	ft_add_command(int cmd_len, char **cmd_line, int index_counter)
{
	t_command	*cmd;
	t_list		*executor_element;

	if (cmd_len > 1)
	{
		cmd = (t_command *)malloc(sizeof(t_command));
		cmd->comm_table = cmd_line;
		cmd->path = NULL;
		cmd->index = index_counter;
		cmd->comm_len = cmd_len;
		cmd->cmd_type = 0;
		ft_command_check(cmd->comm_table[0], &cmd->path, &cmd->cmd_type);
		executor_element = ft_lstnew((void *)cmd);
		ft_lstadd_back(&(g_access.parser2exec), executor_element);
	}
	else
		ft_free_split(cmd_line);
}

/**
	@brief Handles adding main commands (non-redirects) to linked list.
	@param cmd_len Command length value.
	@param cmd_line Command line array.
	@param index_counter Pointer to the index counter.
	@param return_flag Pointer to the error value of parser functions.
	@return None.
	@exception Handles pipe limit error.
*/
static void	ft_add_main_cmd(int cmd_len, char **cmd_line, \
	int *index_counter, int *return_flag)
{
	if (*return_flag == 0)
	{
		ft_add_command(cmd_len, cmd_line, *index_counter);
		(*index_counter)++;
		if (*index_counter > PIPE_LIMIT)
			*return_flag = ft_parser_error_handler(&(g_access.parser2exec), \
				&(g_access.lexor2parser), FT_ERROR_PARSER_PIPE_LIMIT);
	}
	else
		ft_free_split(cmd_line);
}

/**
	@brief Initiates the main parser variables.
	@param index Pointer to the index counter.
	@param lex_element Pointer to the current element of the lexor.
	@param return_flag Pointer to the error value of parser functions.
	@return None.
*/
static void	ft_parser_init(int *index, t_list **lex_element, int *return_flag)
{
	*index = 0;
	*lex_element = g_access.lexor2parser;
	*return_flag = 0;
}

/**
	@brief Resets the value of command line and its length.
	@param cmd_len Pointer to command length value.
	@param cmd_line Pointer to command line array.
	@return None.
*/
static void	ft_parser_cmd_line_reset(int *cmd_len, char ***cmd_line)
{
	*cmd_len = 0;
	*cmd_line = NULL;
}

/**
	@brief Transforms the linke list from the parser into a link list
		with commands and their attributes (path, type, index).
		Deals also with errors due to i.e. wrong user input.
	@return Returns error flag (0 if no error).
*/
int	ft_parser(void)
{
	int		index;
	t_list	*lex_element;
	char	**cmd_line;
	int		cmd_len;
	int		return_flag;

	ft_parser_init(&index, &lex_element, &return_flag);
	while (return_flag == 0 && lex_element != NULL)
	{
		ft_parser_cmd_line_reset(&cmd_len, &cmd_line);
		while (return_flag == 0 && lex_element != NULL)
		{
			return_flag = ft_parser_string_handler(&lex_element, &cmd_line, \
				&cmd_len, index);
			if (return_flag != 0)
				break ;
			lex_element = lex_element->next;
		}
		if (return_flag == 1 || return_flag == 3)
			return_flag--;
		cmd_line = add_to_line(cmd_line, NULL, &cmd_len);
		ft_add_main_cmd(cmd_len, cmd_line, &index, &return_flag);
	}
	ft_free_linked_list(&(g_access.lexor2parser), FT_LIST_TYPE_WORD, 1);
	return (return_flag);
}

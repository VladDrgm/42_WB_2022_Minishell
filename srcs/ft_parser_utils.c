/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parser_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamuller <mamuller@student.42wolfsburg>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/22 21:57:51 by mamuller          #+#    #+#             */
/*   Updated: 2022/02/23 11:40:13 by mamuller         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/minishell.h"

/**
	@brief Creates new array which is one element longer than line.
		It copies the line to it and adds new string as last element.
		The array shouldn't be null terminated. The length of line array
		is in line_len, which is adjusted in this function.
	@param line Array of original line array.
	@param new_str Element to be added.
	@param line_len Pointer to length of line array.
	@return Returns the appended array.
*/
char	**add_to_line(char **line, char *new_str, int *line_len)
{
	char	**new_line;
	int		counter;

	new_line = (char **)malloc(sizeof(char *) * ((*line_len) + 1));
	counter = 0;
	while (counter < *line_len)
	{
		new_line[counter] = line[counter];
		counter++;
	}
	new_line[counter] = new_str;
	(*line_len)++;
	if (line != NULL)
		free(line);
	return (new_line);
}

/**
	@brief Handles error message print and memory management in case of error.
	@param parser_list Pointer to linked list from parser to executer.
	@param lexor_list Pointer to linked list from lexor to parser.
	@param msg Pointer to error message to be printed.
	@return Returns 2 when called to indicate error.
*/
int	ft_parser_error_handler(t_list **parser_list, t_list **lexor_list, \
	const char *msg)
{
	ft_smart_free((void **)&(g_access.last_return));
	g_access.last_return = ft_itoa(2);
	write(2, msg, ft_strlen(msg));
	ft_free_linked_list(parser_list, FT_LIST_TYPE_COMMAND, 1);
	ft_free_linked_list(lexor_list, FT_LIST_TYPE_WORD, 1);
	return (2);
}

/**
	@brief Checks if string is redirect character >, <, << or >>.
	@param str String to be checked.
	@return 1 if redirect character else 0.
*/
int	is_redirect(char *str)
{
	if (!ft_strcmp(str, ">") || !ft_strcmp(str, "<") || \
		!ft_strcmp(str, ">>") || !ft_strcmp(str, "<<"))
		return (1);
	return (0);
}

/**
	@brief Checks if string is pipe character |.
	@param str String to be checked.
	@return 1 if pipe character else 0.
*/
int	is_pipe(char *str)
{
	if (!ft_strcmp(str, "|"))
		return (1);
	return (0);
}

/**
	@brief Checks command name and assign command type variables properly.
		Also calls function to assign the path of a system executables.
	@param str First element of user input.
	@param cmd_path Pointer to command path variable.
	@param cmd_type Pointer to command type flag.
	@return 0 on builtin, system command or redirect and -1 on error type.
*/
int	ft_command_check(char *str, char **cmd_path, int *cmd_type)
{
	int	err;

	if (!ft_strcmp(str, "pwd") || !ft_strcmp(str, "cd") || \
		!ft_strcmp(str, "echo") || !ft_strcmp(str, "export") || \
		!ft_strcmp(str, "unset") || !ft_strcmp(str, "env") || \
		!ft_strcmp(str, "exit"))
	{
		*cmd_type = FT_CMD_TYPE_BUILT_IN;
		return (0);
	}
	else if (!ft_strcmp(str, "<<") || !ft_strcmp(str, "<") || \
		!ft_strcmp(str, ">>") || !ft_strcmp(str, ">"))
	{
		*cmd_type = FT_CMD_TYPE_REDIRECT;
		return (0);
	}
	err = path_finder(str, cmd_path);
	if (err == 0)
		*cmd_type = FT_CMD_TYPE_SYSTEM;
	else if (err == -1)
		*cmd_type = FT_CMD_TYPE_ERROR;
	return (err);
}

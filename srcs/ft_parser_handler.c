/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parser_handler.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamuller <mamuller@student.42wolfsburg>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/22 21:57:51 by mamuller          #+#    #+#             */
/*   Updated: 2022/02/22 22:06:25 by mamuller         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/minishell.h"

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
		*return_flag = ft_error_handler(&(g_access.parser2exec), \
			&(g_access.lexor2parser), FT_ERROR_PARSER_UNEX_TOKEN_NL);
		return (-1);
	}
	if (((t_word *)((*lex_element)->content))->type == FT_SPECIAL_CHAR_STRING)
	{
		ft_smart_free((void **)&(cmd_line_red[0]));
		free(cmd_line_red);
		*return_flag = ft_error_handler(&(g_access.parser2exec), \
			&(g_access.lexor2parser), FT_ERROR_PARSER_UNEX_TOKEN);
		return (-1);
	}
	cmd_line_red[1] = ft_strdup(((t_word *)((*lex_element)->content))->address);
	ft_add_command(3, cmd_line_red, index_counter);
	return (0);
}

static int	ft_pipe_handler(t_list **lex_element, int *return_flag, int cmd_len)
{
	if (cmd_len == 0)
		*return_flag = ft_error_handler(&(g_access.parser2exec), \
			&(g_access.lexor2parser), FT_ERROR_PARSER_UNEX_TOKEN_PIPE);
	else
	{
		*lex_element = (*lex_element)->next;
		if (*lex_element == NULL)
			*return_flag = ft_error_handler(&(g_access.parser2exec), \
				&(g_access.lexor2parser), FT_ERROR_PARSER_UNEX_TOKEN_PIPE);
	}
	return (-1);
}

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
		if (ft_pipe_handler(lex_element, return_flag, cmd_len) == -1)
			return (1);
	}
	else
	{
		*return_flag = ft_error_handler(&(g_access.parser2exec), \
			&(g_access.lexor2parser), FT_ERROR_PARSER_UNEX_TOKEN);
		return (1);
	}
	return (0);
}

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

int	ft_string_handler(t_list **lex_element, \
	char ***cmd_line, int *cmd_len, int index_counter)
{
	int	return_flag;

	return_flag = 0;
	if (((t_word *)((*lex_element)->content))->type == FT_SPECIAL_CHAR_STRING)
	{
		if (ft_special_char_string_handler(lex_element, &return_flag, \
			*cmd_len, index_counter))
			return (return_flag);
	}
	else if (((t_word *)((*lex_element)->content))->type == FT_STRING)
		ft_normal_char_string_handler(*lex_element, cmd_line, cmd_len);
	if (*cmd_len > PARSER_TABLE_LEN_LIMIT)
	{
		return_flag = ft_error_handler(&(g_access.parser2exec), \
			&(g_access.lexor2parser), FT_ERROR_PARSER_ARG_OVERFLOW);
		return (return_flag);
	}
	return (return_flag);
}
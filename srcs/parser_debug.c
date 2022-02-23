/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parser_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamuller <mamuller@student.42wolfsburg>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/22 21:57:51 by mamuller          #+#    #+#             */
/*   Updated: 2022/02/22 21:57:52 by mamuller         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/minishell.h"


/*
**  @brief Handels printing of t_command
**  @param input: Void pointer to t_command
*/
static void	print_element_parser(void *input)
{
	t_command	*cmd;
	int 		test_c;

	cmd = (t_command *)input;
	test_c = 0;
	// printf("Len is %d\n", cmd->comm_len);

	printf("Command type is:%d\n", cmd->cmd_type);
	printf("Length       is %d\n", cmd->comm_len);
	printf("Index       is %d\n", cmd->index);
	printf("Table        is:\n");
	while(test_c < (cmd->comm_len))
	{
		// printf("1\n");
		if (cmd->comm_table[test_c] == NULL)
			printf("0\n");
		else
			printf("%s\n", cmd->comm_table[test_c]);

		// printf("2\n");
		test_c++;
	}
	printf("*****************************************************\n");
}


/*
**  @brief Prints out linked list of with t_command in content
**  @param input: t_list pointer to first element in linked list
*/
void	print_list_parse(t_list *el)
{
	ft_lstiter(el, print_element_parser);
}


/*
**  @brief Free linked list of with t_command in content
**  @param input: t_list pointer to first element in linked list
*/
/* void	ft_free_parser(void *parser)
{
	int i;
	t_command *cmd;

	i = 0;
	cmd = (t_command *)parser;
    while (i < cmd->comm_len)
    {
        free(cmd->comm_table[i]);
        i++;
    }
	if (cmd->path != NULL)
		free(cmd->path);
	free(cmd->comm_table);
	free(parser);
} */

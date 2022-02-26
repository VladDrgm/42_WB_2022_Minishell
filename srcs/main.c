/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbanfi <dbanfi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/26 13:20:12 by dbanfi            #+#    #+#             */
/*   Updated: 2022/02/26 13:20:12 by dbanfi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/minishell.h"

t_global	g_access;

/**
	@brief Runs readline and enables and disables SIGINT signal.
	@return None.
*/
static void	ft_readline(void)
{
	g_access.inter = 1;
	g_access.read_line2lexor = readline(CRED FT_SHELL_NAME RESET);
	g_access.inter = 0;
}

/**
	@brief Minshell loop with lexor, parser and executor.
	@param envp System environmental variables to be passed to
		execution function for non-builtins as array of strings.
	@return None.
*/
static void	ft_minishell(char **envp)
{
	int	temp;

	while (1)
	{
		ft_readline();
		if (g_access.read_line2lexor == NULL)
		{
			write(1, "\b\bexit\n", 7);
			break ;
		}
		if (*(g_access.read_line2lexor) == 0)
			continue ;
		add_history(g_access.read_line2lexor);
		temp = ft_lexor();
		if (temp != -1)
		{
			temp = ft_parser();
			if (temp == 2)
				continue ;
			ft_executor(envp);
		}
		else
			continue ;
	}
}

int	main(int argc, char **argv, char **envp)
{
	int	temp;

	ft_signal_setup();
	if (argc > 1)
		printf("Invalid number of arguments for %s with %s\n", argv[0], envp[0]);
	ft_initiator(envp, argv[0]);
	ft_minishell(envp);
	temp = ft_atoi(g_access.last_return);
	free_global();
	exit (temp);
}

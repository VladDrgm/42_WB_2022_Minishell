/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_signal_handler.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzivanov <dzivanov@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 11:54:27 by dzivanov          #+#    #+#             */
/*   Updated: 2022/02/21 11:56:45 by dzivanov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/minishell.h"

/*
**	rl_on_new_line();
**	Possibility that function does not exist on iMacs, comment out if
**	evaluator has mac
**
**	CTRL + C = SIGINT
**	CTRL + \ = SIGQUIT
*/

void	ft_sigint_handler(int sig)
{
	if (sig == SIGINT && g_access.inter == 1)
	{
		printf("\b\b    ");
		printf("\n");
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
}

void	ft_sigquit_handler(int sig)
{
	if (sig == SIGQUIT && g_access.inter == 1)
	{
		write(1, "\b\b  \b\b", 6);
		rl_redisplay();
	}
}

void	ft_signal_setup(void)
{
	signal(SIGINT, ft_sigint_handler);
	signal(SIGQUIT, ft_sigquit_handler);
}

/*
**
**	CTRL + C = SIGINT
**	CTRL + \ = SIGQUIT
*/

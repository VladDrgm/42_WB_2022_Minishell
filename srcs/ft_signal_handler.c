/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_signal_handler.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbanfi <dbanfi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/26 15:24:38 by dbanfi            #+#    #+#             */
/*   Updated: 2022/02/26 15:24:39 by dbanfi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/minishell.h"

/**
	@brief Makes new readline input line and delets input from last line
		Called on Ctrl+C. (Works properly on linux.)
	@param sig: Signal number.
	@return None.
	@exception Insert "rl_replace_line("", 0);" on line 21 to make it work
		properly.Aveliable only with linux readline library
*/
static void	ft_sigint_handler(int sig)
{
	if (sig == SIGINT && g_access.inter == 1)
	{
		printf("\b\b    ");
		printf("\n");
		rl_on_new_line();
		rl_redisplay();
	}
}

/**
	@brief Ignores signal. Called on Ctrl+/.
	@param sig: Signal number.
	@return None.
*/
static void	ft_sigquit_handler(int sig)
{
	if (sig == SIGQUIT && g_access.inter == 1)
	{
		write(1, "\b\b  \b\b", 6);
		rl_redisplay();
	}
}

/**
	@brief Activates signal handeling of SIGQUIT (Ctrl+/)
		and SIGINT (Ctrl+C).
	@param sig: Signal number.
	@return None.
*/
void	ft_signal_setup(void)
{
	signal(SIGINT, ft_sigint_handler);
	signal(SIGQUIT, ft_sigquit_handler);
}

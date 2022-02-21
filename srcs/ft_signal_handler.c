#include "../incl/minishell.h"

/*
**	rl_replace_line("", 0);
**	Possibility that function does not exist on iMacs, comment out if
**	evaluator has iMac
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
		// rl_replace_line("", 0);
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

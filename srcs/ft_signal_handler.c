#include "../incl/minishell.h"


//CTRL + C = SIGINT
//CTRL + \ = SIGQUIT

void ft_sigint_handler(int sig)
{
	if(sig == SIGINT && g_access.inter == 1)
	{
		printf("\b\b    ");
		printf("\n");
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
}

void ft_sigquit_handler(int sig)
{
	if(sig == SIGQUIT && g_access.inter == 1)
	{
		write(1, "\b\b  \b\b", 6);
		rl_redisplay();
	}
}

void	ft_signal_setup(void)
{
	signal(SIGINT, ft_sigint_handler);	//ctrl + c
	signal(SIGQUIT, ft_sigquit_handler); /* ctrl + \ */
}
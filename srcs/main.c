#include "../incl/minishell.h"

t_global	g_access;
/*
**	line 20 is dealing with EOF (Ctrl + D)
**	line 22 is dealing with Enter (empty input)
*/

int	main(int argc, char **argv, char**envp)
{
	ft_signal_setup();
	if (argc > 1)
		printf("Invalid number of arguments for %s with %s\n", argv[0], envp[0]);
	ft_initiator(envp, argv[0]);
	while (1)
	{
		g_access.inter = 1;
		g_access.read_line2lexor = readline(CRED "minishe11 1.0> " RESET);
		g_access.inter = 0;
		if (g_access.read_line2lexor == NULL)
			break ;
		if (*(g_access.read_line2lexor) == 0)
			continue ;
		add_history(g_access.read_line2lexor);
		if (lexor() != -1)
		{
			if (parser() == 2)
				continue ;
			if (executor(envp) == 0)
				break ;
		}
	}
	free_global();
	return (0);
}

#include "../incl/minishell.h"

t_global g_access;

int	main(int argc, char **argv, char**envp)
{


// ************************************Part 1******************************
 	//char	*args;
	//t_list	*lexer2parser_list;
	//t_list	*parser2executor_list;
	int		temp;

	ft_signal_setup();
	if (argc > 1)
		printf("Invalid number of arguments for %s with %s\n", argv[0], envp[0]);
	ft_initiator(envp, argv[0]);
	temp = 0;
	while (1)
	{
		temp = 0;
		g_access.inter = 1;
		g_access.read_line2lexor = readline(">");
		g_access.inter = 0;
		if (g_access.read_line2lexor == NULL) //dealing with EOF (Ctrl + D)
			break;
		if (*(g_access.read_line2lexor) == 0) //dealing with Enter (empty input)
			continue;
		add_history(g_access.read_line2lexor);
		//temp = lexor(&lexer2parser_list, args);
		temp = lexor();
		if (temp != -1)
		{
			//temp = parser(&lexer2parser_list, &parser2executor_list);
			temp = parser();
			if (temp == 2)
			{
				continue;
				// exit(1);
			}

			//g_access.parser2exec = &parser2executor_list;

			// temp = minishell_execute();
			temp = executor(envp);
			//free(g_access.parser2exec); //This should be handled by executor at some point
			//g_access.parser2exec = NULL;
			if (temp == 0)
				break;
		}
		else
			continue;
	}
	// printf("before segfault5\n");
	free_global();
	// rl_clear_history();
	return (0);
}

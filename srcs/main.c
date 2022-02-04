#include "../incl/minishell.h"

t_global g_access;

int	main(int argc, char **argv, char**envp)
{


// ************************************Part 1******************************
 	//char	*args;
	//t_list	*lexer2parser_list;
	//t_list	*parser2executor_list;
	int		temp;


	if (argc > 1)
		printf("Invalid number of arguments for %s with %s\n", argv[0], envp[0]);
	ft_initiator(envp);
	temp = 0;
	while (1)
	{
		g_access.read_line2lexor = readline(">");
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
			if (temp != 0)
				break ;
			//g_access.parser2exec = &parser2executor_list;

			// temp = minishell_execute();
			temp = executor(envp);
			free(g_access.parser2exec); //This should be handled by executor at some point
			g_access.parser2exec = NULL;
			if (temp == 0)
				break;
		}
		else
			break;
	}
	free_global();
	return (0);
}

#include "../incl/minishell.h"
#include "../incl/minishe11.h"

int	main(int argc, char **argv, char**envp)
{


// ************************************Part 1******************************
 	char	*args;
	t_list	*lexer2parser_list;
	t_list	*parser2executor_list;
	int		temp;

	if (argc > 1)
		printf("Invalid number of arguments for %s with %s\n", argv[0], envp[0]);
	init_global();
	args = NULL;
	// args++;
	temp = 0;
	while (1)
	{
		args = readline(">");
		add_history(args);
		lexer2parser_list = NULL;
		parser2executor_list = NULL;
		temp = lexor(&lexer2parser_list, args);
		if (temp != -1)
		{
			temp = parser(&lexer2parser_list, &parser2executor_list);
			if (temp != 0)
				break ;
			//executor(shell);
		}
	}
// ************************************Part 2******************************
/*	t_shell *shell;
	char	*line;
	char	**args;
	int		status;

	if (argc > 1)
		printf("Invalid number of arguments for %s\n", argv[0]);
	shell = malloc(sizeof(t_shell) * 1);
	line = NULL;
	status = 1;
	// int i = 0;
	// while (envp[i])
	// {
	// 	printf("%s\n", envp[i]);
	// 	i++;
	// }
	ft_initiator_exc(&(shell), envp);
	// Run command loop.
	while (status)
	{
		line = readline(">");
		args = minishell_split_line(line); // !!!!!!!!!! Lexor/Parser Part !!!!!!!!!!!
		status = minishell_execute(args, shell); // !!!!!!!!!! Execution Part !!!!!!!!!!!
		free(line);
		free(args);
	}
	// free(args);
	return (0);*/
}

#include "../incl/minishell.h"

int	main(void)
{
	char	*args;
	t_list	*lexer2parser_list;
	t_list	*parser2executor_list;
	int		temp;

	args = NULL;
	// args++;
	temp = 0;
	lexer2parser_list = NULL;
	parser2executor_list = NULL;
	while (1)
	{
		args = readline(">");
		temp = lexor(&lexer2parser_list, args);
		if (temp == 0)
		{
			temp = parser(&lexer2parser_list, &parser2executor_list);
			if (temp != 0)
				break ;
			executor();
		}
	}
	// free(args);
	return (0);
}

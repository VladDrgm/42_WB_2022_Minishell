#include "../incl/minishell.h"
#include "../incl/minishe11.h"

int	main(int argc, char **argv, char**envp)
{
	char	*args;
	t_list	*list;
	int		temp;
	t_shell *shell;
	argc++;
	if (!argv[1])
		printf("%s\n", envp[1]);

	shell = NULL;
	args = NULL;
	// args++;
	temp = 0;
	list = NULL;
	while (1)
	{
		args = readline(">");
		temp = lexor(&list, args);
		if (temp == 0)
		{
			temp = parser();
			if (temp != 0)
				break ;
			// executor(shell, envp);
		}
	}
	// free(args);
	return (0);
}

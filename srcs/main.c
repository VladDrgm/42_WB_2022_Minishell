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

	shell = malloc(sizeof(t_shell) * 1);
	args = NULL;
	// args++;
	temp = 0;
	list = NULL;
	ft_initiator_exc(&(shell), envp);
	while (1)
	{
		args = readline(">");
		temp = lexor(&list, args);
		if (temp == 0)
		{
			temp = parser();
			if (temp != 0)
				break ;
			executor(shell);
		}
	}
	// free(args);
	return (0);
}

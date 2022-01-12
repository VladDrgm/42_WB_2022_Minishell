#include "../incl/minishell.h"

int	main(void)
{
	char	*args;
	t_list	*list;
	int		temp;

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
			executor();
		}
	}
	// free(args);
	return (0);
}

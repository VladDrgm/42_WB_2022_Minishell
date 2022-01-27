#include "../incl/pipex.h"

void	ft_double_safety_check(int i, int y)
{
	if ((i < 0) || (y < 0))
	{
		perror("Return Value -1 detected");
		exit(EXIT_FAILURE);
	}
}

void	ft_file_descriptor_killer(void)
{
	printf("There has been an issue i fucked up\n");
	// close(STDIN_FILENO);
	// close(STDOUT_FILENO);
	// close(STDERR_FILENO);
	// exit(EXIT_FAILURE);
}

void	ft_add_lst(t_content	**content, char **argv, int i, char **p_s)
{
	(*content)->cmd_n_flags = ft_split(argv[i + 2], ' ');
	(*content)->path = ft_get_cmd_path((*content)->cmd_n_flags[0], p_s);
	(*content)->index = i;
}

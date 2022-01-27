/* ************************************************************************** */
/*                                                                            */
#include "../incl/pipex.h"

int	main(int argc, char **argv, char **envp)
{
	t_list	*cmd_list;

	cmd_list = NULL;
	if (argc < 5)
	{
		ft_putstr_fd("Too few arguments for executing pipex!\n", 1);
		exit(EXIT_FAILURE);
	}
	ft_check_input_file(argv[1], argv[argc - 1]);
	ft_check_output_file(argv[argc - 1]);
	ft_make_cmd_list(argv, envp, argc, &cmd_list);
	ft_pipex(argc, argv, cmd_list, envp);
	return (0);
}

void	ft_check_input_file(char *filename, char *outputfile)
{
	int	fd_output;

	fd_output = 0;
	if (access(filename, F_OK) == 0)
	{
		if (access(filename, R_OK) == 0)
			return ;
		else
		{
			perror("Input file without reading rights");
			fd_output = open(outputfile, O_WRONLY | O_CREAT | O_TRUNC, 0777);
			close(fd_output);
			ft_close_fd();
			exit(EXIT_FAILURE);
		}
	}
	else
	{
		perror("Invalid input file");
		fd_output = open(outputfile, O_WRONLY | O_CREAT | O_TRUNC, 0777);
		close(fd_output);
		ft_close_fd();
		exit(EXIT_FAILURE);
	}
}

void	ft_check_output_file(const char *filename)
{
	if (access(filename, F_OK) == 0)
	{
		if (access(filename, W_OK) != 0)
		{
			perror("Output file without writing rights");
			ft_close_fd();
			exit(EXIT_FAILURE);
		}
	}
	else
		return ;
}

void	ft_make_cmd_list(char **argv, char **envp, int argc, t_list **cmd_list)
{
	t_content	*content;
	t_list		*elem;
	char		**path_list;
	int			j;
	int			i;

	j = 0;
	i = 0;
	path_list = ft_split_path(envp);
	while (i + 2 <= argc - 2)
	{
		content = ft_calloc(1, sizeof(t_content));
		content->cmd_n_flags = ft_split(argv[i + 2], ' ');
		content->path = ft_get_cmd_path(content->cmd_n_flags[0], path_list);
		content->index = j;
		elem = ft_lstnew(content);
		ft_lstadd_back(cmd_list, elem);
		if (content->path == NULL)
			ft_exit_on_invalid_cmd(path_list, cmd_list, content, elem);
		j++;
		i++;
	}
	ft_free_split(path_list);
}

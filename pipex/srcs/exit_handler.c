#include "../incl/pipex.h"

void	ft_close_fd(void)
{
	close(STDIN_FILENO);
	close(STDOUT_FILENO);
	close(STDERR_FILENO);
}

void	ft_free_split(char **split)
{
	int	i;

	i = 0;
	while (split[i] != NULL)
	{
		free(split[i]);
		i++;
	}
	free(split);
}

void	ft_free_list(t_list *head)
{
	t_list	*tmp;

	while (head != NULL)
	{
		tmp = head;
		head = head->next;
		ft_free_split(((t_content *)(tmp->content))->cmd_n_flags);
		if (((t_content *)(tmp->content))->path != NULL)
			free(((t_content *)(tmp->content))->path);
		else
			continue ;
		free(tmp->content);
		free(tmp);
	}
}

void	ft_exit_on_error(t_list **cmd_list, char *error_msg)
{
	perror(error_msg);
	ft_free_list(*cmd_list);
	ft_close_fd();
	exit(EXIT_FAILURE);
}

void	ft_exit_on_invalid_cmd(char **path_list, t_list **cmd_list, \
		t_content *content, t_list *elem)
{
	ft_free_split(path_list);
	ft_free_list(*cmd_list);
	free(content);
	free(elem);
	perror("Invalid Command");
	ft_close_fd();
	exit(EXIT_FAILURE);
}

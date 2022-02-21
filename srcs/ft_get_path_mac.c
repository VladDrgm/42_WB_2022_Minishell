#include "../incl/minishell.h"

void ft_get_PATH(void)
{
	int fd;
	char *s;
	char *path;
	t_list *ptr;
	t_env_var *env_var;
	char *temp;

	ptr = g_access.env;
	while(ptr)
	{
		if (!ft_strncmp(((t_env_var *)(ptr->content))->name, "PATH=", 5))
		{
			if (((t_env_var *)(ptr->content))->value == NULL || ft_strlen(((t_env_var *)(ptr->content))->value) == 0)
				break;
			else
				return;
		}
		ptr = ptr->next;
	}
	fd = open("/etc/paths", O_RDONLY);
	s = get_next_line(fd);
	path = ft_strdup("");
	while (s != NULL)
	{
		if (s[ft_strlen(s) - 1] == '\n')
			temp = ft_substr(s, 0, ft_strlen(s) - 1);
		else
			temp = ft_strdup(s);
		free(s);
		if (ft_strlen(path) != 0)
			path = ft_strjoin_with_dfree(temp, ft_strjoin_with_scnd_free(":", path));
		else
		{
			path = ft_strdup(temp);
			if (temp != NULL)
				free(temp);
		}
		s = get_next_line(fd);
	}
	close(fd);
	if (ptr != NULL)
	{
		if (((t_env_var *)(ptr->content))->value != NULL)
			free(((t_env_var *)(ptr->content))->value);
		((t_env_var *)(ptr->content))->value = path;
	}
	else
	{
		env_var = (t_env_var *)malloc(sizeof(t_env_var));
		env_var->name = ft_strdup("PATH=");
		env_var->value = path;
		ft_lstadd_back(&(g_access.env), ft_lstnew(env_var));
	}
}


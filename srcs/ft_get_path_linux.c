#include "../incl/minishell.h"

void ft_get_PATH(void)
{
	int fd;
	char *s;
	t_list *ptr;
	t_env_var *env_var;

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
	fd = open("/etc/environment", O_RDONLY);
	s = get_next_line(fd);
	printf("s: %s\n", s);
	while (s != NULL)
	{
		printf("s in while: %s\n", s);
		if (!ft_strncmp(s, "PATH=", 5))
		{
			if (ptr != NULL)
			{
				printf("Test 1\n");
				if (((t_env_var *)(ptr->content))->value != NULL)
					free(((t_env_var *)(ptr->content))->value);
				printf("Test 2\n");
				((t_env_var *)(ptr->content))->value = ft_substr(s, 6, ft_strlen(s) - 6 - 1);
				printf("((t_env_var *)(ptr->content))->value: %s\n", ((t_env_var *)(ptr->content))->value);
			}
			else
			{
				printf("Test 3\n");
				env_var = (t_env_var *)malloc(sizeof(t_env_var));
				env_var->name = ft_substr(s, 0, 5);
				env_var->value = ft_substr(s, 6, ft_strlen(s) - 6 - 2);
				printf("Test 4\n");
				ft_lstadd_back(&(g_access.env), ft_lstnew(env_var));
				printf("Test 5\n");
				printf("((t_env_var *)(ptr->content))->name: %s\n", ((t_env_var *)(ptr->content))->name);
				printf("((t_env_var *)(ptr->content))->value: %s\n", ((t_env_var *)(ptr->content))->value);
			}
		}
		printf("Test 6\n");
		if (s != NULL)
		{
			free(s);
			s = get_next_line(fd);
		}
	}
	close(fd);
}


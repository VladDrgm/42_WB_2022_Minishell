#include "../incl/minishell.h"

void	delone(void *content)
{
	t_env_var *env_var;

	env_var = (t_env_var *) content;

	free(env_var->name);
	free(env_var->value);
	free(content);
}

char *env_value_finder(char *name) //FINDS THE EQUIVALENT VALUE OF A ENV VAR
{
	t_list *ptr = g_access.env;

	while (ptr != NULL)
	{
		if (!ft_strncmp(((t_env_var *)(ptr->content))->name, name, ft_strlen(name)))
		{
			if (((t_env_var *)(ptr->content))->value != NULL)
				return (((t_env_var *)(ptr->content))->value);
		}
		ptr = ptr->next;
	}
	return NULL;
}

/**
	@brief Functionality: ft_update_env.
	@param shell -> structure formed out of command lines, paths, anything read as input from user
	@param to_search the string to be looked for inside the envp variable
	@param to_replace the string that will replace 'to_search'
	@return None.
	@todo check if it really behives as intended
 */

void ft_update_env(char *to_search, char *to_replace)
{
	t_list *ptr;
	ptr = g_access.env;

	while(ptr!= NULL)
	{
		if (!ft_strncmp(((t_env_var*)(ptr->content))->name, to_search, ft_strlen(to_search)))
		{
			if (((t_env_var*)(ptr->content))->value != NULL)
				free(((t_env_var*)(ptr->content))->value);
			((t_env_var*)(ptr->content))->value = NULL;
			((t_env_var*)(ptr->content))->value = ft_strdup(to_replace);
		}
		ptr = ptr->next;
	}
}

void ft_last_arg(char **args, pid_t pid)
{
	int	i;

	i = 0;
	if (!args)
		ft_update_create_env("_", "", pid);
	while (args[i] != NULL)
		i++;
	printf("i = %d\n", i);
	printf("0 = %s\n", args[0]);
	printf("1 = %s\n", args[1]);
	printf("1 = %s\n", args[i - 1]);
	ft_update_create_env("_", args[i - 1], pid);
}

// void ft_update_create_(char *to_update)
// {

// }
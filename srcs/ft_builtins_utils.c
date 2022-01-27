#include "../incl/minishell.h"

void	*delone(void *content)
{
	t_env_var *env_var;

	env_var = (t_env_var *) content;

	free(env_var->name);
	free(env_var->value);
	free(content);
	return NULL;
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

char *temp_value_finder(char *name)
{
	t_list *ptr = g_access.temp_env;

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
			free(((t_env_var*)(ptr->content))->value);
			((t_env_var*)(ptr->content))->value = NULL;
			((t_env_var*)(ptr->content))->value = ft_strdup(to_replace);
		}
		ptr = ptr->next;
	}
}
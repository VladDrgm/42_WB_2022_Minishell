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
	t_list *ptr = ((t_list *)(*g_access.env));

	while (ptr != NULL)
	{
		if (!ft_strncmp(((t_env_var *)(ptr->content))->name, name, ft_strlen(name)))
		{
			return (((t_env_var *)(ptr->content))->value);
		}
		ptr = ptr->next;
	}
	return NULL;
}
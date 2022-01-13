#include "../incl/minishe11.h"


void ft_create_envlist(t_list **env, char **envp)
{
	int i;
	i = 1;
	while (envp[i])
	{
		ft_lstadd_back(env, ft_lstnew(ft_strdup(envp[i])));
		i++;
	}
}

void ft_initiator_exc(t_shell **shell, char **envp)
{
	(*shell)->env = NULL;
	ft_create_envlist(&((*shell)->env), envp);
}
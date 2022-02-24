/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtins_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbanfi <dbanfi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/25 17:29:14 by dbanfi            #+#    #+#             */
/*   Updated: 2022/02/25 17:29:14 by dbanfi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/minishell.h"

/**
	@brief
	@param content
	@return None.
 */
void	delone(void *content)
{
	t_env_var	*env_var;

	env_var = (t_env_var *) content;
	free(env_var->name);
	free(env_var->value);
	free(content);
}

//FINDS THE EQUIVALENT VALUE OF A ENV VAR
/**
	@brief
	@param name
	@return *char.
 */
char	*env_value_finder(char *name)
{
	t_list	*ptr;

	ptr = g_access.env;
	while (ptr != NULL)
	{
		if (!ft_strncmp(((t_env_var *)(ptr->content))->name, name, \
			ft_strlen(name)))
		{
			if (((t_env_var *)(ptr->content))->value != NULL)
				return (((t_env_var *)(ptr->content))->value);
		}
		ptr = ptr->next;
	}
	return (NULL);
}

/**
	@brief Functionality: ft_update_env.
	@param to_search the string to be looked for inside the envp variable
	@param to_replace the string that will replace 'to_search'
	@return None.
 */
void	ft_update_env(char *to_search, char *to_replace)
{
	t_list	*ptr;

	ptr = g_access.env;
	while (ptr != NULL)
	{
		if (!ft_strncmp(((t_env_var *)(ptr->content))->name, \
			to_search, ft_strlen(to_search)))
		{
			if (((t_env_var *)(ptr->content))->value != NULL)
				free(((t_env_var *)(ptr->content))->value);
			((t_env_var *)(ptr->content))->value = NULL;
			((t_env_var *)(ptr->content))->value = ft_strdup(to_replace);
		}
		ptr = ptr->next;
	}
}

/**
	@brief
	@param args
	@param pid
	@return None.
 */
void	ft_last_arg(char **args, pid_t pid)
{
	int	i;

	i = 0;
	if (!*args)
		ft_update_create_env("_", "", pid);
	while (args[i] != NULL)
		i++;
	ft_update_create_env("_", args[i - 1], pid);
}

/**
	@brief 
	@param args
	@param pid
	@param lreturn
	@param mode
	@return None.
 */
void	ft_set_lasts(char **args, int pid, int lreturn, int mode)
{
	if (mode == 1)
		ft_last_arg(args, pid);
	else if (mode == 2)
	{
		ft_smart_free((void **)&(g_access.last_return));
		g_access.last_return = ft_itoa(lreturn);
	}
	else if (mode == 3)
	{
		ft_smart_free((void **)&(g_access.last_return));
		g_access.last_return = ft_itoa(lreturn);
		ft_last_arg(args, pid);
	}
}

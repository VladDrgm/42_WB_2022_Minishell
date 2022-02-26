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
	@brief Finds the value of env var
	@param name Serached key.
	@return Value of found env var else NULL
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
	@brief Updates value of already exisisting env.
	@param to_search The string to be looked for inside the env variable
	@param to_replace The string that will replace 'to_search'
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
	@brief Updates _ env var with value of last argument of input.
	@param args Array of arguments. 
	@param pid Proccess id.
	@return None.
	@exception Sets env var _ to empty string.
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
	@brief Updates _ env var and/or(depends on mode) exit value.
	@param args Array of arguments. 
	@param pid Proccess id.
	@param lreturn Exit value.
	@param mode Mode of the function call.
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

/**
	@brief Updates already existing env var else creates new env var.
	@param env Key of env var.
	@param value New value of env var.
	@param pid Proccess id.
	@return None.
 */
void	ft_update_create_env(char *env, char *value, pid_t pid)
{
	t_list	*ptr;
	char	*args[3];

	ptr = g_access.env;
	while (ptr != NULL)
	{
		if (ft_strncmp(((t_env_var *)(ptr->content))->name, env, \
			ft_strlen(env)) == 0)
		{
			if ((ft_strlen(((t_env_var *)(ptr->content))->name) - 1) == \
				ft_strlen(env))
			{
				ft_smart_free((void **)&(((t_env_var *)(ptr->content))->value));
				((t_env_var *)(ptr->content))->value = ft_strdup(value);
				return ;
			}
		}
		ptr = ptr->next;
	}
	args[0] = "export";
	args[1] = ft_strjoin_with_free(ft_strjoin(env, "="), value);
	args[2] = NULL;
	minishell_export(args, pid);
	ft_smart_free((void **)&args[1]);
}

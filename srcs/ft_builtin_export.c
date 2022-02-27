/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtin_export.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbanfi <dbanfi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/27 12:24:34 by dbanfi            #+#    #+#             */
/*   Updated: 2022/02/27 12:32:06 by dbanfi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/minishell.h"

/**
	@brief Handels sorting and printing content of env var list.
	@return Always returns 1.
	@exception Also prints variables without a value.(No = in key)
 */
static int	ft_single_export(void)
{
	t_list	*env_cpy;

	env_cpy = ft_copy_env();
	ft_print_sorted_copy(env_cpy);
	if (env_cpy)
		ft_free_linked_list(&env_cpy, FT_LIST_TYPE_ENV_VAR, 1);
	return (1);
}

/**
	@brief Updates value of env var if it already exists in env var list.
	@param env_var Pointer of structure env var to update env var list with.
	@return Int.
 */
static int	ft_check_existing_env(t_env_var **env_var)
{
	t_list	*ptr;

	ptr = g_access.env;
	while (ptr)
	{
		if (!ft_strncmp((*env_var)->name, \
			((t_env_var *)(ptr->content))->name, ft_strlen((*env_var)->name)))
		{
			free(((t_env_var *)(ptr->content))->value);
			((t_env_var *)(ptr->content))->value = ft_strdup((*env_var)->value);
			free((*env_var)->name);
			free((*env_var)->value);
			free(*env_var);
			*env_var = NULL;
			return (1);
		}
		ptr = ptr->next;
	}
	return (0);
}

/**
	@brief Adds env var to the end of the env var list if argument is valid.
	@param args List of args.
	@param i Current argument.
	@param j Delimiter between key and value of added env var.
	@param valid Validity flag.
	@return None.
	@exception If there is no env var value sets value to NULL.
		With or without =. With no = it is only visible with export.
 */
static void	ft_export_add_env(char **args, int i, int j, int valid)
{
	t_env_var	*env_var;

	if ((args[i][j] == '=' || args[i][j] == '\0') && valid)
	{
		env_var = (t_env_var *)malloc(sizeof(t_env_var));
		if (args[i][j] == '=')
		{
			env_var->name = ft_substr(args[i], 0, j + 1);
			env_var->value = ft_strdup(&(args[i][j + 1]));
		}
		else
		{
			env_var->name = ft_strdup(&(args[i][0]));
			env_var->value = NULL;
		}
		if (!ft_check_existing_env(&env_var))
			ft_lstadd_back(&(g_access.env), ft_lstnew(env_var));
	}
}

/**
	@brief Builtin command: export. Adds env var to list
		or displays env var list in alphabedical order.
	@param args List of args.
	@param pid Proccess id.
	@return Always returns 1, to continue execution.
 */
int	minishell_export(char **args, pid_t pid)
{
	int	len;
	int	j;
	int	i;
	int	valid;

	len = 0;
	while (args[len] != 0)
		len++;
	valid = 1;
	ft_set_lasts(NULL, pid, 0, FT_LAST_RETURN_MODE);
	if (args[1] == NULL && pid == 0)
	{
		ft_last_arg(args, pid);
		return (ft_single_export());
	}
	i = 1;
	while (i < len)
	{
		j = ft_env_name_check(args[i], &valid, pid, FT_EXPORT_MES_TYPE);
		ft_export_add_env(args, i, j, valid);
		i++;
	}
	ft_last_arg(args, pid);
	return (1);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbanfi <dbanfi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/25 17:07:17 by dbanfi            #+#    #+#             */
/*   Updated: 2022/02/25 17:07:17 by dbanfi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/minishell.h"

/**
	@brief
	@param env_cpy
	@param ptr_cpy
	@param en_var
	@return None.
 */
static void	ft_copy_env_big_list_handler(t_list **env_cpy, \
	t_list *ptr_cpy, t_env_var *env_var)
{
	t_list	*tmp;

	if (ft_strcmp(env_var->name, ((t_env_var *)(ptr_cpy->content))->name) < 0)
		ft_lstadd_front(env_cpy, ft_lstnew(env_var));
	else if (ft_strcmp(env_var->name, \
		((t_env_var *)(ft_lstlast(*env_cpy)->content))->name) > 0)
		ft_lstadd_back(env_cpy, ft_lstnew(env_var));
	else
	{
		while (ptr_cpy->next != NULL)
		{
			if (ft_strcmp(env_var->name, \
				((t_env_var *)(ptr_cpy->content))->name) > 0 && \
				ft_strcmp(env_var->name, \
				((t_env_var *)(ptr_cpy->next->content))->name) < 0)
			{
				tmp = ft_lstnew(env_var);
				tmp->next = ptr_cpy->next;
				ptr_cpy->next = tmp;
				break ;
			}
			ptr_cpy = ptr_cpy->next;
		}
	}
}

static void	ft_copy_env_var_creation(t_env_var **env_var, t_list *ptr_env)
{
	*env_var = (t_env_var *)malloc(sizeof(t_env_var));
	(*env_var)->name = ft_strdup(((t_env_var *)(ptr_env->content))->name);
	(*env_var)->value = ft_strdup(((t_env_var *)(ptr_env->content))->value);
}

/**
	@brief
	@return t_list.
 */
t_list	*ft_copy_env(void)
{
	t_list		*env_cpy;
	t_list		*ptr_env;
	t_list		*p_cp;
	t_env_var	*env;

	ptr_env = g_access.env;
	env_cpy = NULL;
	while (ptr_env)
	{
		p_cp = env_cpy;
		ft_copy_env_var_creation(&env, ptr_env);
		if (ft_lstsize(env_cpy) == 0)
			ft_lstadd_back(&(env_cpy), ft_lstnew(env));
		else if (ft_lstsize(env_cpy) == 1)
		{
			if (ft_strcmp(env->name, ((t_env_var *)(p_cp->content))->name) > 0)
				ft_lstadd_back(&(env_cpy), ft_lstnew(env));
			else
				ft_lstadd_front(&(env_cpy), ft_lstnew(env));
		}
		else
			ft_copy_env_big_list_handler(&env_cpy, p_cp, env);
		ptr_env = ptr_env->next;
	}
	return (env_cpy);
}

/**
	@brief
	@param ptr
	@return None.
 */
static void	ft_print_sorted_copy_value(t_list *ptr)
{
	int	i;

	if (((t_env_var *)(ptr->content))->value != NULL)
	{
		write(1, "\"", 1);
		i = 0;
		while (((t_env_var *)(ptr->content))->value[i] != '\0')
		{
			if (((t_env_var *)(ptr->content))->value[i] == '$' \
				|| (((t_env_var *)(ptr->content))->value)[i] == '\"')
				write(1, "\\", 1);
			write(1, &((t_env_var *)(ptr->content))->value[i], 1);
			i++;
		}
		write(1, "\"", 1);
	}
}

/**
	@brief
	@param env_cpy
	@return None.
 */
void	ft_print_sorted_copy(t_list *env_cpy)
{
	t_list	*ptr;

	ptr = env_cpy;
	while (ptr)
	{
		if (ft_strncmp(((t_env_var *)(ptr->content))->name, "_=", 2))
		{
			write(1, "declare -x ", 11);
			write(1, ((t_env_var *)(ptr->content))->name, \
				ft_strlen(((t_env_var *)(ptr->content))->name));
			ft_print_sorted_copy_value(ptr);
			write(1, "\n", 1);
		}
		ptr = ptr->next;
	}
}

/**
	@brief
	@return Int.
 */
int	ft_single_export(void)
{
	t_list	*env_cpy;

	env_cpy = ft_copy_env();
	ft_print_sorted_copy(env_cpy);
	if (env_cpy)
		ft_free_linked_list(&env_cpy, FT_LIST_TYPE_ENV_VAR, 1);
	return (1);
}

/**
	@brief
	@param env_var
	@return Int.
 */
int	ft_check_existing_env(t_env_var **env_var)
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

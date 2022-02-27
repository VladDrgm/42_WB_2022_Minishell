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
	@brief Puts copied node in correct place in copied env var list. 
		Used for copied list that is longer than 2 after adding current node.
	@param env_cpy Sorted copy of env var linked list(not full).
	@param ptr_cpy First element of copied list.
	@param env_var Env var to be adde to copied list.
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

/**
	@brief Creates a copy of env var list node content.
	@param env_var Pointer to copy of a node content.
	@param ptr_var Node to be copied.
	@return None.
 */
static void	ft_copy_env_var_creation(t_env_var **env_var, t_list *ptr_env)
{
	*env_var = (t_env_var *)malloc(sizeof(t_env_var));
	(*env_var)->name = ft_strdup(((t_env_var *)(ptr_env->content))->name);
	(*env_var)->value = ft_strdup(((t_env_var *)(ptr_env->content))->value);
}

/**
	@brief Creates a copy of env var list with alphabetical order.
	@return Sorted copy of env var list.
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
	@brief Prints value of env var value in right format.
	@param ptr Pointer to env var node.
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
	@brief Printing sorted env var list with ALL variables.
		Prints "declare -x " before every variable and puts value inside "".
	@param env_cpy
	@return None.
	@exception _ env var isn't printed.
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

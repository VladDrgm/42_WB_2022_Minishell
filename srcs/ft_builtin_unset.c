/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtin_unset.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbanfi <dbanfi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/27 12:24:34 by dbanfi            #+#    #+#             */
/*   Updated: 2022/02/27 12:34:19 by dbanfi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/minishell.h"

/**
	@brief Removes env var if it is the first node
		of the env var linked list.
	@param ptr Pointer to the head of env var linked list.
	@param i Index of current argument.
	@param args List of args.
	@param valid Validity flag.
	@return None.
 */
static int	ft_unset_first_node(t_list *ptr, char **args, int i, int valid)
{
	if (ft_strlen(args[i]) == \
		ft_strlen(((t_env_var *)(ptr->content))->name) - 1 && valid)
	{
		if (!ft_strncmp(args[i], ((t_env_var *)(ptr->content))->name, \
			ft_strlen(args[i])))
		{
			if (ft_strncmp(args[i], "_", ft_strlen(args[i])))
			{
				g_access.env = ptr->next;
				ft_lstdelone(ptr, del_env_var);
				return (1);
			}
		}
	}
	return (0);
}

/**
	@brief Removes env var if it is in the middle
		of the env var linked list.
	@param ptr Pointer to the head of env var linked list.
	@param i Index of current argument.
	@param args List of args.
	@return None.
 */
static void	ft_unset_middle_node(t_list *ptr, int i, char **args)
{
	t_list	*temp;

	if (ft_strncmp(args[i], "_", 1))
	{
		temp = ptr->next;
		ptr->next = ptr->next->next;
		ft_lstdelone(temp, del_env_var);
	}
}

/**
	@brief Removes env var if it is the last node
		of the env var linked list.
	@param ptr Pointer to the head of env var linked list.
	@param i Index of current argument.
	@param args List of args.
	@return None.
 */
static void	ft_unset_last_node(t_list *ptr, int i, char **args)
{
	if (ft_strncmp(args[i], "_", 1))
	{
		ft_lstdelone(ptr->next, del_env_var);
		ptr->next = NULL;
	}
}

/**
	@brief Handels removing of env var if it isn't
		in the first node of the env var linked list.
	@param ptr Pointer to the head of env var linked list.
	@param i Index of current argument.
	@param args List of args.
	@param valid Validity flag.
	@return None.
 */
static void	ft_unset_nonfirst_node_handler(t_list *ptr, int i, \
	char **args, int valid)
{
	while (ptr->next != NULL && valid)
	{
		if (ft_strlen(args[i]) == \
			ft_strlen(((t_env_var *)(ptr->next->content))->name) - 1)
		{
			if (!ft_strncmp(args[i], \
				((t_env_var *)(ptr->next->content))->name, ft_strlen(args[i])))
			{
				if (ptr->next->next != NULL)
					ft_unset_middle_node(ptr, i, args);
				else
					ft_unset_last_node(ptr, i, args);
				break ;
			}
		}
		ptr = ptr->next;
	}
}

/**
	@brief Builtin command: unset. Removes env var from the env var list.
	@param args List of args.
	@param pid Proccess id.
	@return Always returns 1, to continue execution.
 */
int	minishell_unset(char **args, pid_t pid)
{
	t_list	*ptr;
	int		valid;
	int		len;
	int		i;

	valid = 1;
	ft_set_lasts(args, pid, 0, FT_LAST_FULL_MODE);
	len = 0;
	while (args[len] != 0)
		len++;
	i = 1;
	while (i < len)
	{
		ptr = g_access.env;
		ft_env_name_check(args[i], &valid, pid, FT_UNSET_MES_TYPE);
		if (!ft_strncmp(args[i], "PWD", ft_strlen(args[i])))
			ft_smart_free((void **)&(g_access.pwd));
		if (!ft_unset_first_node(ptr, args, i, valid))
			ft_unset_nonfirst_node_handler(ptr, i, args, valid);
		i++;
	}
	return (1);
}

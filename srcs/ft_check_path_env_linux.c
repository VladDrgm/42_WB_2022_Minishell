/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_path_env_linux.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbanfi <dbanfi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 11:57:20 by dbanfi            #+#    #+#             */
/*   Updated: 2022/02/21 11:57:20 by dbanfi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/minishell.h"

/**
	 @brief Creates or updates PATH to found value.
	 @param s String to be saved into PATH.
	 @param ptr Pointer to PATH node in envlist or NULL if PATH not found.
	 @return None.
*/
static void	ft_create_update_path(char *s, t_list *ptr)
{
	t_env_var	*env_var;

	if (!ft_strncmp(s, "PATH=", 5))
	{
		if (ptr != NULL)
		{
			if (((t_env_var *)(ptr->content))->value != NULL)
				free(((t_env_var *)(ptr->content))->value);
			((t_env_var *)(ptr->content))->value = \
				ft_substr(s, 6, ft_strlen(s) - 6 - 1);
		}
		else
		{
			env_var = (t_env_var *)malloc(sizeof(t_env_var));
			env_var->name = ft_substr(s, 0, 5);
			env_var->value = ft_substr(s, 6, ft_strlen(s) - 6 - 2);
			ft_lstadd_back(&(g_access.env), ft_lstnew(env_var));
		}
	}
}

/**
	 @brief Checks if there is valid PATH env and finds it.
	 @param ptr Pointer to env linked list.
	 @return 1 on a valid path else 0.
	 @exception PATH with empty value is considered invalid.
*/
static int	ft_check_path(t_list **ptr)
{
	while (*ptr)
	{
		if (!ft_strncmp(((t_env_var *)((*ptr)->content))->name, "PATH=", 5))
		{
			if (((t_env_var *)((*ptr)->content))->value == NULL \
				|| ft_strlen(((t_env_var *)((*ptr)->content))->value) == 0)
				return (0);
			else
				return (1);
		}
		*ptr = (*ptr)->next;
	}
	return (0);
}

/**
	 @brief Handling unexistent PATH in copied env list. Opens sys file.
	 @return None.
*/
void	ft_check_path_env(void)
{
	int			fd;
	char		*s;
	t_list		*ptr;
	int			found;

	ptr = g_access.env;
	found = ft_check_path(&ptr);
	if (found)
		return ;
	fd = open("/etc/environment", O_RDONLY);
	s = get_next_line(fd);
	while (s != NULL)
	{
		ft_create_update_path(s, ptr);
		if (s != NULL)
		{
			free(s);
			s = get_next_line(fd);
		}
	}
	close(fd);
}

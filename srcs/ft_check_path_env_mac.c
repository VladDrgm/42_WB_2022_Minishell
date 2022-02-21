/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_path_env_mac.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbanfi <dbanfi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 12:45:02 by dbanfi            #+#    #+#             */
/*   Updated: 2022/02/21 12:45:02 by dbanfi           ###   ########.fr       */
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

	if (ptr != NULL)
	{
		if (((t_env_var *)(ptr->content))->value != NULL)
			free(((t_env_var *)(ptr->content))->value);
		((t_env_var *)(ptr->content))->value = s;
	}
	else
	{
		env_var = (t_env_var *)malloc(sizeof(t_env_var));
		env_var->name = ft_strdup("PATH=");
		env_var->value = s;
		ft_lstadd_back(&(g_access.env), ft_lstnew(env_var));
	}
}

/**
	 @brief Concatenate the path from given file discrptor.
	 @param fd File descriptor
	 @return None.
*/
static char	*ft_get_path(int fd)
{
	char	*s;
	char	*path;
	char	*temp;

	s = get_next_line(fd);
	path = ft_strdup("");
	while (s != NULL)
	{
		if (s[ft_strlen(s) - 1] == '\n')
			temp = ft_substr(s, 0, ft_strlen(s) - 1);
		else
			temp = ft_strdup(s);
		ft_smart_free((void **)&s);
		if (ft_strlen(path) != 0)
			path = ft_strjoin_with_dfree(temp, \
				ft_strjoin_with_scnd_free(":", path));
		else
		{
			ft_smart_free((void **)&path);
			path = ft_strdup(temp);
			ft_smart_free((void **)&temp);
		}
		s = get_next_line(fd);
	}
	return (path);
}

/**
	 @brief Handling unexistent PATH in copied env list. Opens sys file.
	 @return None.
*/
void	ft_check_path_env(void)
{
	t_list	*ptr;
	char	*path;
	int		fd;

	ptr = g_access.env;
	while (ptr)
	{
		if (!ft_strncmp(((t_env_var *)(ptr->content))->name, "PATH=", 5))
		{
			if (((t_env_var *)(ptr->content))->value == NULL \
				|| ft_strlen(((t_env_var *)(ptr->content))->value) == 0)
				break ;
			else
				return ;
		}
		ptr = ptr->next;
	}
	fd = open("/etc/paths", O_RDONLY);
	path = ft_get_path(fd);
	close(fd);
	ft_create_update_path(path, ptr);
}

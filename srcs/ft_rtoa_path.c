/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamuller <mamuller@student.42wolfsburg>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/25 21:31:51 by mamuller          #+#    #+#             */
/*   Updated: 2022/02/25 21:31:51 by mamuller         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/minishell.h"

/**
	@brief Handels absolute path value inside relative path and
		subdirs of current working dir.
	@param rel_path Relative path to be transformed.
	@param abs_path Pointer to absolute path. (output value)
	@return None.
 */
static int	ft_abs_path_handler(char *rel_path, char **abs_path)
{
	int	i;

	i = 0;
	if (ft_strnstr(rel_path, ".", ft_strlen(rel_path)) == NULL)
	{
		if (rel_path[0] == '/')
		{
			*abs_path = ft_strdup(rel_path);
			return (1);
		}
		if (g_access.dp == NULL)
		{
			*abs_path = getcwd(NULL, 0);
			while (getcwd(*abs_path, i) == NULL)
				i++;
			*abs_path = ft_strjoin_with_free(ft_strjoin_with_free(*abs_path, \
				"/"), rel_path);
		}
		else
			*abs_path = ft_strjoin_with_free(ft_strjoin(g_access.dp, \
				"/"), rel_path);
		return (1);
	}
	return (0);
}

/**
	@brief Removes last level of dir from path value inside path_helper.
	@param path_helper Pointer to a string with path value. To be manipulated.
	@return Returns 1 if path value can't be changed(root dir) else return 0.
 */
static int	ft_parent_dir_handler(char **path_helper)
{
	char	*path_ptr;
	char	*path_helper_free;

	path_ptr = ft_strrchr(*path_helper, '/');
	if (path_ptr != NULL)
	{
		path_helper_free = *path_helper;
		*path_helper = ft_substr(*path_helper, 0, \
			ft_strlen(*path_helper) - ft_strlen(path_ptr));
		if (ft_strlen(*path_helper) == 0)
		{
			*path_helper = ft_strjoin_with_free(*path_helper, "/");
			ft_smart_free((void **)&path_helper_free);
			return (1);
		}
		ft_smart_free((void **)&path_helper_free);
	}
	return (0);
}

/**
	@brief Merges relative path and current working dir into absolute path.
	@param rel_path Relative path to be transformed.
	@param path_helper Pointer to a string with current working dir.
		To be manipulated.
	@return None.
 */
static void	ft_rel_path_handler(char **path_helper, char *rel_path)
{
	char	**arg_split;
	char	**split_ptr;

	arg_split = ft_split(rel_path, '/');
	split_ptr = arg_split;
	while (*split_ptr != NULL)
	{
		if (!ft_strncmp(*split_ptr, "..", 2) && ft_strlen(*split_ptr) == 2)
		{
			if (ft_parent_dir_handler(path_helper))
				break ;
		}
		else if (!ft_strncmp(*split_ptr, ".", 1) && ft_strlen(*split_ptr) == 1)
		{
			split_ptr++;
			continue ;
		}
		else
			*path_helper = ft_strjoin_with_dfree(*path_helper, \
				ft_strjoin("/", *split_ptr));
		split_ptr++;
	}
	ft_free_split(arg_split);
}

/**
	@brief Transforms relative path to absolute path.
	@param rel_path Relative path to be transformed.
	@param abs_path Pointer to absolute path. (output value)
	@return None.
 */
void	ft_rtoa_path(char *rel_path, char **abs_path)
{
	char	*path_helper;

	if (ft_abs_path_handler(rel_path, abs_path))
		return ;
	path_helper = NULL;
	if (g_access.dp != NULL)
		path_helper = ft_strdup(g_access.dp);
	else if (g_access.pwd != NULL)
		path_helper = ft_strdup(g_access.pwd);
	else
		ft_set_global_pwd(&path_helper);
	ft_rel_path_handler(&path_helper, rel_path);
	*abs_path = path_helper;
}

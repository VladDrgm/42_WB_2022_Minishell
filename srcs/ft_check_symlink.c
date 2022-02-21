/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_symlink.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbanfi <dbanfi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 15:12:48 by dbanfi            #+#    #+#             */
/*   Updated: 2022/02/21 17:46:22 by dbanfi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/minishell.h"

static int	ft_next_sub_dir(struct stat *buf, char **path_substr)
{
	char	*str_ptr;
	char	*path_substr_free;

	path_substr_free = NULL;
	str_ptr = NULL;
	ft_smart_free((void **)&buf);
	str_ptr = NULL;
	str_ptr = ft_strrchr(*path_substr, '/');
	if (str_ptr != NULL)
	{
		path_substr_free = *path_substr;
		*path_substr = ft_substr(*path_substr, 0, \
			ft_strlen(*path_substr) - ft_strlen(str_ptr));
		ft_smart_free((void **)&path_substr_free);
	}
	else
		ft_smart_free((void **)path_substr);
}

static void	ft_full_free(struct stat *buf, char *path_substr)
{
	if (buf != NULL)
		free(buf);
	if (path_substr != NULL)
		free(path_substr);
}

static void	ft_error_message(char *arg, pid_t pid)
{
	if (pid == 0)
	{
		write(2, "minishell: cd: ", 15);
		write(2, arg, ft_strlen(arg));
		perror(" ");
	}
}

int	ft_check_symlink(char *path, char *arg, pid_t pid)
{
	struct stat	*buf;
	char		*path_substr;

	path_substr = ft_strdup(path);
	while (path_substr != NULL)
	{
		buf = ft_calloc(sizeof(struct stat), 1);
		if ((ft_strlen(path_substr) != 0) && (lstat(path_substr, buf) == -1))
		{
			ft_error_message(arg, pid);
			ft_full_free(buf, path_substr);
			return (-1);
		}
		if (S_ISLNK(buf->st_mode))
		{
			ft_full_free(buf, path_substr);
			return (SYMLINK);
		}
		else
			ft_next_sub_dir(buf, &path_substr);
	}
	ft_full_free(buf, path_substr);
	return (NOT_SYMLINK);
}

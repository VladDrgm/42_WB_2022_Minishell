/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_path_finder.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbanfi <dbanfi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/22 21:57:51 by mamuller          #+#    #+#             */
/*   Updated: 2022/02/26 16:42:56 by dbanfi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/minishell.h"

/**
	@brief Checks if the combination of path and executable is accessible
		and updated cmd_path in that case.
	@param split Array list of paths from env variables.
	@param cmd_path Pointer to full executable path.
	@param str Name of the executable.
	@param tmp Pointer to temporary path holder.
	@return 1 on success else 0.
	@exception If path was found errno needs to be set success value again
		in case it changed to previous access fails.
*/
static int	ft_path_checker(char **split, char **cmd_path, char *str, char *tmp)
{
	int	i;

	i = 0;
	if (split != NULL)
	{
		while (split[i])
		{
			tmp = ft_strjoin_with_scnd_free(split[i], ft_strjoin("/", str));
			if (access(tmp, F_OK) == 0)
			{
				errno = 0;
				*cmd_path = ft_strdup(tmp);
				ft_free_split(split);
				ft_smart_free((void **)&tmp);
				return (1);
			}
			else
				ft_smart_free((void **)&tmp);
			i++;
		}
		ft_free_split(split);
	}
	ft_smart_free((void **)&tmp);
	errno = 0;
	return (0);
}

/**
	@brief Finds the correct path to an executable (str) in 
		path env var or curent directory. Error message
		printed in case no path is found.
	@param str Name of the executable.
	@param cmd_path Pointer to full executable path.
	@return 0 on success else -1.
*/
int	path_finder(char *str, char **cmd_path)
{
	char	*path;
	char	**split;
	char	*temp_path;

	temp_path = NULL;
	if (access(str, F_OK) == 0)
	{
		*cmd_path = ft_strdup(str);
		return (0);
	}
	path = env_value_finder("PATH");
	if (path != NULL)
	{
		split = ft_split(ft_strchr(path, '/'), ':');
		if (split != NULL)
			if (ft_path_checker(split, cmd_path, str, temp_path))
				return (0);
	}
	write(2, "minishell: ", 12);
	write(2, str, ft_strlen(str));
	write(2, ": No such file or directory\n", 28);
	ft_smart_free((void **)&(g_access.last_return));
	g_access.last_return = ft_itoa(127);
	return (-1);
}

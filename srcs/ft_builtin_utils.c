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
	@brief Removes repeating slashes '/'.
	@param cp String to be cleaned of slashes.
	@return None.
 */
void	ft_path_cleaner(char **cp)
{
	char	*current_path_free;
	int		i;
	int		j;

	i = 0;
	while ((*cp)[i] != '\0')
	{
		j = i;
		while ((*cp)[j] == '/')
			j++;
		if ((j != i && (*cp)[j] == '\0') || (j > i + 1))
		{
			if (!ft_strcmp(*cp, "/"))
				break ;
			current_path_free = *cp;
			if ((*cp)[j] == '\0' && i != 0)
				*cp = ft_strjoin_with_free(ft_substr(*cp, 0, i), &(*cp)[j]);
			else
				*cp = ft_strjoin_with_free(ft_substr(*cp, 0, i + 1), &(*cp)[j]);
			ft_smart_free((void **)&current_path_free);
			i = 0;
			continue ;
		}
		i++;
	}
}

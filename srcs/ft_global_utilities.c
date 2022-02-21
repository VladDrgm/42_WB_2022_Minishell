/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_global_utilities.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdragomi <vdragomi@42student.wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 11:59:20 by vdragomi          #+#    #+#             */
/*   Updated: 2022/02/21 13:15:06 by vdragomi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/minishell.h"


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

void	ft_set_lasts(char **args, int pid, int lreturn)
{
	if (g_access.last_return != NULL)
		free(g_access.last_return);
	g_access.last_return = ft_itoa(lreturn);
	ft_last_arg(args, pid);
}

void free_secure(void **s)
{
      if (*s != NULL)
        free(*s);
      *s = NULL;
}
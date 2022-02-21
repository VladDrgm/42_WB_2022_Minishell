/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_global_utilities.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdragomi <vdragomi@42student.wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 11:59:20 by vdragomi          #+#    #+#             */
/*   Updated: 2022/02/21 12:02:48 by vdragomi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/minishell.h"

void	ft_set_last(char **args, int pid, int lreturn)
{
	if (g_access.last_return != NULL)
		free(g_access.last_return);
	g_access.last_return = ft_itoa(lreturn);
	ft_last_arg(args, pid);
}
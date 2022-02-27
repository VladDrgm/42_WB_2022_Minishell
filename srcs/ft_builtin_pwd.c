/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtin_pwd.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbanfi <dbanfi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/27 12:24:34 by dbanfi            #+#    #+#             */
/*   Updated: 2022/02/27 12:24:44 by dbanfi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/minishell.h"

/**
	@brief Builtin command: pwd. Prints current working directory.
	@param args List of args.
	@param pid Proccess id.
	@return Always returns 1, to continue execution.
	@exception Doesn't check arguments.
 */
int	minishell_pwd(char **args, pid_t pid)
{
	char	*buf;
	int		i;

	i = 1;
	ft_set_lasts(args, pid, 0, FT_LAST_FULL_MODE);
	if (args[0] == NULL)
		return (0);
	if (pid == 0)
	{
		if (g_access.dp == NULL)
		{
			buf = getcwd(NULL, 0);
			while (getcwd(buf, i) == NULL)
				i++;
			write(1, buf, ft_strlen(buf));
			free(buf);
		}
		else
			write(1, g_access.dp, ft_strlen(g_access.dp));
		write(1, "\n", 1);
	}
	return (1);
}

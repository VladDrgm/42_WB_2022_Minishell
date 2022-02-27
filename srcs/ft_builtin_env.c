/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtin_env.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbanfi <dbanfi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/25 16:20:24 by dbanfi            #+#    #+#             */
/*   Updated: 2022/02/27 12:24:06 by dbanfi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/minishell.h"

/**
	 @brief Bultin command: env. Prints all existing env variables.
	 	Doesn't print Variables without value.
	 @param args List of arguments.
	 @param pid Proccess id.
	 @return Always returns 1, to continue executing.
 */
int	minishell_env(char **args, pid_t pid)
{
	t_list	*ptr;

	ft_set_lasts(args, pid, 0, FT_LAST_FULL_MODE);
	if (ft_strncmp(args[0], "env", 3))
		return (0);
	ptr = g_access.env;
	if (pid == 0)
	{
		while (ptr != NULL)
		{
			if (((t_env_var *)(ptr->content))->value != NULL)
			{
				write(1, ((t_env_var *)(ptr->content))->name, \
					ft_strlen(((t_env_var *)(ptr->content))->name));
				write(1, ((t_env_var *)(ptr->content))->value, \
					ft_strlen(((t_env_var *)(ptr->content))->value));
				write(1, "\n", 1);
			}
			if (ptr->next != NULL)
				ptr = ptr->next;
			else
				break ;
		}
	}
	return (1);
}

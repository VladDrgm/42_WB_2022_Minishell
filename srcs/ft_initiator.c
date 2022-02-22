/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_initiator.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbanfi <dbanfi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 11:19:28 by dbanfi            #+#    #+#             */
/*   Updated: 2022/02/21 11:19:28 by dbanfi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/minishell.h"

/**
	 @brief Initiates all necessary variables for running the minishell.
	 @param envp Original environmental variables list.
	 @param executable Name of the minishell executable.
	 @return None.
	 @exception Runtime linked lists are initialized to NULL.
 */
void	ft_initiator(char **envp, char *executable)
{
	g_access.signals = 0;
	g_access.inter = 0;
	g_access.last_return = ft_itoa(0);
	g_access.pwd = NULL;
	g_access.dp = NULL;
	ft_envlist_cpy(envp);
	ft_check_pwd_env();
	ft_update_shell_env(executable);
	ft_check_path_env();
	ft_init_builtins();
	g_access.lexor2parser = NULL;
	g_access.parser2exec = NULL;
	g_access.read_line2lexor = NULL;
}

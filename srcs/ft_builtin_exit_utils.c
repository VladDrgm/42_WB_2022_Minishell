/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbanfi <dbanfi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/25 16:28:20 by dbanfi            #+#    #+#             */
/*   Updated: 2022/02/25 16:28:20 by dbanfi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/minishell.h"

/**
	@brief Prints error message according to input. Exits with exit_value.
	@param str1 The first part of error message.
	@param str2 Option for the seconed part of error message.
	@param str3 Option for the third part of error message.
	@param exit_value Value of exit.
	@return None.
	@exception Prints normal exit message if the first string is just "exit\n".
 */
void	ft_exit_error_handler(char *str1, char *str2, char *str3, \
	int exit_value)
{
	if (ft_strncmp(str1, "exit\n", ft_strlen(str1)))
		write(2, str1, ft_strlen(str1));
	else
		write(1, str1, ft_strlen(str1));
	if (str2 != NULL)
		write(2, str2, ft_strlen(str2));
	if (str3 != NULL)
		write(2, str3, ft_strlen(str3));
	exit(exit_value);
}

/**
	@brief Exit function to be called in child processes frees global struct
		and closes standard fds. Exits with exit_value.
	@param exit_value Value of exit.
	@return None.
 */
void	ft_child_exit(int exit_value)
{
	free_global();
	close(STDERR_FILENO);
	close(STDIN_FILENO);
	close(STDOUT_FILENO);
	exit(exit_value);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit_utils2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdragomi <vdragomi@42student.wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 12:46:46 by vdragomi          #+#    #+#             */
/*   Updated: 2022/02/21 13:33:35 by vdragomi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/minishell.h"

static void	ft_parent_error_handler(char **args)
{
	long long int	num_arg;

	num_arg = ft_atoll(args[1]);
	if (!((num_arg < 0 && args[1][0] != '-') || \
		(num_arg > 0 && args[1][0] == '-')))
	{
		if (num_arg >= 0 && num_arg <= 255)
			ft_exit_error_handler("exit\n", NULL, NULL, num_arg);
		else if (num_arg > 255)
			ft_exit_error_handler("exit\n", NULL, NULL, num_arg % 256);
		else if (num_arg < 0)
			ft_exit_error_handler("exit\n", NULL, NULL, \
				256 - ((num_arg * -1) % 256));
	}
}

int	ft_parent_exiter(int pid, char **args)
{
	int	len;

	len = 0;
	while (args[len] != NULL)
		len++;
	if (len > 2 && !ft_digit_check(args[1]))
	{
		write(2, "minishell: exit: too many arguments\n", 36);
		ft_set_lasts(args, pid, 1);
		return (1);
	}
	else if (len == 1)
		ft_exit_error_handler("exit\n", NULL, NULL, \
			ft_atoi(g_access.last_return));
	else if (!ft_digit_check(args[1]))
	{
		ft_parent_error_handler(args);
	}
	else if (len >= 2)
		ft_exit_error_handler("exit\nminishell: exit: ", args[1], \
			": numeric argument required\n", 255);
	exit(2);
}

static void	ft_child_error_handler(char **args)
{
	long long int	num_arg;

	num_arg = ft_atoll(args[1]);
	if (!((num_arg < 0 && args[1][0] != '-') || \
		(num_arg > 0 && args[1][0] == '-')))
	{
		if (num_arg >= 0 && num_arg <= 255)
			ft_exit(num_arg);
		else if (num_arg > 255)
			ft_exit(num_arg % 256);
		else if (num_arg < 0)
			ft_exit(256 - ((num_arg * -1) % 256));
	}
}

void	ft_child_exiter(char **args)
{
	int	len;

	len = 0;
	while (args[len] != NULL)
		len++;
	if (len > 2 && !ft_digit_check(args[1]))
		ft_exit(1);
	else if (len == 1)
		ft_exit(ft_atoi(g_access.last_return));
	else if (!ft_digit_check(args[1]))
		ft_child_error_handler(args);
	else if (len >= 2)
		ft_exit(255);
	ft_exit(2);
}

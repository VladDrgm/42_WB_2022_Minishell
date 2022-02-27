/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtins.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbanfi <dbanfi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/25 16:20:24 by dbanfi            #+#    #+#             */
/*   Updated: 2022/02/25 16:20:24 by dbanfi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/minishell.h"

/**
	@brief Handels exit function called in pipeline. Errors are not printed.
	@param i Number of arguments.
	@param args List of arguments.
	@return None.
 */
static void	ft_exit_multiple_child_handler(int *i, char **args)
{
	long long int	nb;

	while (args[*i] != NULL)
		(*i)++;
	if (*i > 2 && !ft_digit_check(args[1]))
		ft_child_exit(1);
	else if (*i == 1)
		ft_child_exit(ft_atoi(g_access.last_return));
	else if (!ft_digit_check(args[1]))
	{
		if (ft_atoll(args[1], &nb))
			ft_child_exit(255);
		if (!((nb < 0 && args[1][0] != '-') || (nb > 0 && args[1][0] == '-')))
		{
			if (nb >= 0 && nb <= 255)
				ft_child_exit(nb);
			else if (nb > 255)
				ft_child_exit(nb % 256);
			else if (nb < 0)
				ft_child_exit(256 - ((nb * -1) % 256));
		}
	}
	else if (*i >= 2)
		ft_child_exit(255);
	ft_child_exit(2);
}

/**
	@brief Converts the first argument into a number. Checks if it is valid
		and exits with correct value. Prints error if needed.
	@param args List of arguments.
	@return None.
 */
static void	ft_exit_value_cast(char **args)
{
	long long int	num_arg;
	int				err;

	err = ft_atoll(args[1], &num_arg);
	if (err)
		ft_exit_error_handler("exit\nminishell: exit: ", \
			args[1], ": numeric argument required\n", 255);
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

/**
	@brief Handels exit functio in parent when needed. Initiates argument check.
		Prints error if needed.
	@param i Number of arguments.
	@param args List of arguments.
	@return None.
 */
static void	ft_exit_parent_handler(int *i, char **args)
{
	while (args[*i] != NULL)
		(*i)++;
	if (*i > 2 && !ft_digit_check(args[1]))
	{
		write(2, FT_ERROR_EXIT_ARGS_NUM, ft_strlen(FT_ERROR_EXIT_ARGS_NUM));
		ft_set_lasts(NULL, 0, 1, FT_LAST_RETURN_MODE);
		return ;
	}
	else if (*i == 1)
		ft_exit_error_handler("exit\n", NULL, NULL, \
		ft_atoi(g_access.last_return));
	else if (!ft_digit_check(args[1]))
		ft_exit_value_cast(args);
	else if (*i >= 2)
		ft_exit_error_handler("exit\nminishell: exit: ", \
			args[1], ": numeric argument required\n", 255);
	exit(4);
}

/**
	 @brief Builtin command: exit. Exits and/or changes exit value.
	 @param args List of args.
	 @param pid Proccess id.
	 @return Always returns 0, to terminate execution.
 */
int	minishell_exit(char **args, pid_t pid)
{
	int	i;
	int	counter;

	i = 0;
	ft_set_lasts(args, pid, 0, FT_LAST_ARG_MODE);
	counter = ((t_command *)ft_lstlast(g_access.parser2exec)->content)->index;
	if (counter == 0 && pid != 0)
	{
		ft_exit_parent_handler(&i, args);
		return (1);
	}
	else if (counter == 0 && pid == 0)
	{
		while (args[i] != NULL)
			i++;
		if (i > 2 && !ft_digit_check(args[1]))
			ft_child_exit(1);
	}
	else if (counter != 0 && pid == 0)
		ft_exit_multiple_child_handler(&i, args);
	return (0);
}

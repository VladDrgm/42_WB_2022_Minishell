/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtins2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamuller <mamuller@student.42wolfsburg>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/25 21:26:00 by mamuller          #+#    #+#             */
/*   Updated: 2022/02/25 21:26:00 by mamuller         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/minishell.h"

/**
	@brief Prints out arguments.
	@param str List of args.
	@param starter Index of first argument to be printed.
	@param size Number of arguments.
	@param flag Flag for printing NL in the end.
	@return None.
 */
static void	echo_print(char **str, int starter, int size, int flag)
{
	int	i;

	i = starter;
	while (i < size)
	{
		write(1, str[i], ft_strlen(str[i]));
		if (i != size - 1)
			write(1, " ", 1);
		i++;
	}
	if (flag == 0)
		write(1, "\n", 1);
}

/**
	 @brief Check first if we have the mandatory '-' sign.
		Check if the next char is 'n'. Keep going to pass through all n's.
		Check if all elements were n OR if we have some 
		other char different fron n.
	 @param str List of args.
	 @return Returns value of -n flag.
 */
static int	echo_flag(char *str)
{
	int	j;
	int	len;

	len = ft_strlen(str);
	if ((str[0] == '-') && len >= 2)
	{
		if (str[1] == 'n' && len >= 2)
		{
			j = 1;
			while (j < len && str[j] == 'n')
				j++;
			if (j == len)
				return (1);
			else
				return (0);
		}
		else
			return (0);
	}
	else
		return (0);
}

/**
	@brief Handels printing of arguments and flag detection.
	@param args List of args.
	@param len Number of arguments.
	@return None.
 */
static void	echo_print_handler(char **args, int len)
{
	int	flag;
	int	i;
	int	temp;

	flag = 0;
	i = 1;
	while (args[i])
	{
		temp = echo_flag(args[i]);
		flag += temp;
		if (flag == 0 || temp == 0)
			break ;
		else
			i++;
	}
	echo_print(args, i, len, flag);
}

/**
	 @brief Builtin command: echo. Handels printing of arguments.
	 	With or without NL in the end. Flag -n is handled.
	 @param args List of args.
	 @param pid Proccess id.
	 @return Always returns 1.
*/
int	minishell_echo(char **args, pid_t pid)
{
	int	len;

	if (pid == 0)
	{
		len = 0;
		while (args[len] != NULL)
			len++;
		if (args[1] == NULL)
			write(1, "\n", 1);
		else
			echo_print_handler(args, len);
	}
	ft_set_lasts(args, pid, 0, FT_LAST_FULL_MODE);
	return (1);
}

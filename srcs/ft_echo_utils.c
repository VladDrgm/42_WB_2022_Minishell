/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbanfi <dbanfi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/25 21:28:04 by mamuller          #+#    #+#             */
/*   Updated: 2022/02/26 23:57:50 by dbanfi           ###   ########.fr       */
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
void	echo_print(char **str, int starter, int size, int flag)
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
int	echo_flag(char *str)
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

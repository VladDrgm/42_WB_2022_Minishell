/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamuller <mamuller@student.42wolfsburg>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/25 21:28:04 by mamuller          #+#    #+#             */
/*   Updated: 2022/02/25 22:50:39 by mamuller         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/minishell.h"

/**
	@brief
	@param str
	@param starter
	@param size
	@param flag
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
	{
		write(1, "\n", 1);
	}
}

/**
	 @brief 
		- check first if we have the mandatory '-' sign
		- check if the next char is 'n'
		- keep going to pass through all n's
		- check if all elements were n OR if we have some 
		other char different fron n
	 @param str
	 @return Int
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
			{
				j++;
			}
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

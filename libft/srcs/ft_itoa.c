/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdragomi <vdragomi@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 14:53:31 by vdragomi          #+#    #+#             */
/*   Updated: 2021/12/14 14:53:31 by vdragomi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
DESCRIPTION
	Allocates (with malloc(3)) and returns a string representing the 
	integer received as an argument. Negative numbers must be handled.
RETURN VALUE
	The string representing the integer. NULL if the allocation fails.
*/

#include "libft.h"

static void	ft_filldest(char *dest, long long int n, int index)
{
	unsigned int	num;

	if (n < 0)
	{
		dest[0] = '-';
		num = (unsigned int)(n * -1);
	}
	else
		num = (unsigned int)n;
	if (num >= 10)
		ft_filldest(dest, num / 10, index - 1);
	dest[index] = (char)(num % 10 + '0');
}

char	*ft_itoa(long long int n)
{
	char			*dest;
	long long int	num;
	int				count;
	int				neg;

	count = 1;
	neg = 0;
	if (n < 0)
	{
		neg = 1;
		num = (long long int)(n * -1);
	}
	else
		num = (long long int)n;
	while ((num / 10) > 0)
	{
		num = num / 10;
		count++;
	}
	dest = ft_calloc(count + neg + 1, 1);
	if (dest == NULL)
		return (NULL);
	ft_filldest(dest, n, (count + neg) - 1);
	return (dest);
}

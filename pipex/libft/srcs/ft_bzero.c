/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamuller <mamuller@student.42wolfsburg>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/15 20:38:23 by mamuller          #+#    #+#             */
/*   Updated: 2021/11/15 20:38:23 by mamuller         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* DESCRIPTION
	The bzero() function erases the data in the n bytes of the memory
	starting at the location pointed to by s, 	by writing zeros
	(bytes containing '\0') to that area.
RETURN VALUE
	None.
*/

#include "libft.h"

void	ft_bzero(void *s, size_t n)
{
	size_t	i;
	char	*str;

	i = 0;
	str = (char *)s;
	while (i < n)
	{
		str[i] = '\0';
		i++;
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamuller <mamuller@student.42wolfsburg>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/15 20:44:42 by mamuller          #+#    #+#             */
/*   Updated: 2021/11/15 20:44:42 by mamuller         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
DESCRIPTION
	The memcpy() function copies n bytes from memory area src to
	memory area dest. The memory areas must not overlap.
	Use memmove(3) if the memory areas do overlap.
RETURN VALUE
	The memcpy() function returns a pointer to dest.
*/

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t		i;
	char		*dest_p;
	const char	*src_p;

	if (!dest && !src)
		return (NULL);
	i = 0;
	dest_p = dest;
	src_p = src;
	while (i < n)
	{
		dest_p[i] = src_p[i];
		i++;
	}
	return (dest);
}

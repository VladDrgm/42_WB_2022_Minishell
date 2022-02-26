/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbanfi <dbanfi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/26 16:49:19 by dbanfi            #+#    #+#             */
/*   Updated: 2022/02/26 16:49:19 by dbanfi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
DESCRIPTION
	The  memmove() function copies n bytes from memory area src to memory area
	dest. The memory areas may overlap: copying takes place as though the bytes
	in src are first copied into a temporary array that does not overlap src
	or dest, and the bytes are then copied from the temporary array to dest.
RETURN VALUE
	The memmove() function returns a pointer to dest.
*/

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	size_t	i;
	char	*dest_p;
	char	*src_p;

	if (!dest && !src)
		return (NULL);
	dest_p = (char *)dest;
	src_p = (char *)src;
	i = 0;
	if (dest_p < src_p)
	{
		while (i < n)
		{
			dest_p[i] = src_p[i];
			i++;
		}
		return (dest);
	}
	while (n >= 1)
	{
		n--;
		dest_p[i + n] = src_p[n];
	}
	return (dest);
}

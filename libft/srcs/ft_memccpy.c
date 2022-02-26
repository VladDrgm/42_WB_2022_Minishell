/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbanfi <dbanfi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/26 16:48:43 by dbanfi            #+#    #+#             */
/*   Updated: 2022/02/26 16:48:43 by dbanfi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
DESCRIPTION
	The memccpy() function copies no more than n bytes from memory
	area src to memory area dest, stopping when the character c is found.
	If the memory areas overlap, the results are undefined.
RETURN VALUE
	The memccpy() function returns a pointer to the next character in dest
	after c, or NULL if c was not found in the first n characters of src.
*/

#include "libft.h"

void	*ft_memccpy(void *dest, const void *src, int c, size_t n)
{
	size_t				i;
	unsigned char		*dest_p;
	unsigned const char	*src_p;
	unsigned char		*return_dest;

	i = 0;
	dest_p = (unsigned char *)dest;
	src_p = (unsigned const char *)src;
	while (i < n)
	{
		dest_p[i] = src_p[i];
		if ((unsigned char)c == (unsigned char)src_p[i])
		{
			return_dest = &dest_p[i + 1];
			return (return_dest);
		}
		i++;
	}
	return (NULL);
}

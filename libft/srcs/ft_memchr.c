/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbanfi <dbanfi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/26 16:48:52 by dbanfi            #+#    #+#             */
/*   Updated: 2022/02/26 16:48:52 by dbanfi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
DESCRIPTION
	The memchr() function scans the initial n bytes of the memory area pointed
	to by s for the first instance of c. Both c and the bytes of the memory
	area pointed to by s are interpreted as unsigned char.
RETURN VALUE
	The memchr() function returns a pointer to the matching
	byte or NULL if the character does not occur in the given memory area.
*/

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t		i;
	const char	*s_p;

	if (n == 0)
		return (NULL);
	i = 0;
	s_p = s;
	while (i <= n - 1)
	{
		if ((unsigned char)c == (unsigned char)s_p[i])
			return ((void *)&s_p[i]);
		i++;
	}
	return (NULL);
}

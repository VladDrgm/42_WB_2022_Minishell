/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbanfi <dbanfi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/26 16:50:58 by dbanfi            #+#    #+#             */
/*   Updated: 2022/02/26 16:50:58 by dbanfi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
DESCRIPTION
	The strlcat() function concatenates strings respectively. It is
	designed to be safer, more consistent, and less error prone replacement
	strncat(3). Unlike those function, strlcat() take the full size of the
	buffer (not just the length) and guarantee to NUL-terminate the result
	(as long as there is at least one byte free in dst). Note that a byte
	for the NUL should be included in size.  Also note thatstrlcat() only
	operates on true “C” strings. This means for strlcat() both src and
	dst must be NUL-terminated. The strlcat() function appends the
	NUL-terminated string src to the end of dst. It will append at most
	size - strlen(dst) - 1 bytes, NUL-terminating the result.
RETURN VALUE
	The strlcat() function returns the total length of the string they
	tried to create. That means the initial length of dst plus the length
	of src. While this may seem somewhat confusing, it was done to make
	truncation detection simple.

	Note, however, that if strlcat() traverses size characters without finding
	a NUL, the length of the string is considered to be size and the destination
	string will not be NUL-terminated (since there was no space for the NUL).
	This keeps strlcat() from running off the end of a string. In practice this
	should not happen (as it means that either size is incorrect or that dst is
	not a proper “C” string).  The check exists to prevent potential security
	problems in incorrect code.
*/

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	int	i;
	int	dest_len;
	int	src_len;

	i = 0;
	dest_len = (int)ft_strlen(dst);
	src_len = (int)ft_strlen(src);
	if (size == 0)
		return (src_len);
	if (dest_len >= (int)size)
		return (src_len + size);
	while (i < ((int)size - dest_len - 1) && src[i] != '\0')
	{
		dst[dest_len + i] = src[i];
		i++;
	}
	dst[dest_len + i] = '\0';
	return (src_len + dest_len);
}

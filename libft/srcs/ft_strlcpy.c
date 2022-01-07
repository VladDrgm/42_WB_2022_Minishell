/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdragomi <vdragomi@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 14:55:40 by vdragomi          #+#    #+#             */
/*   Updated: 2021/12/14 14:55:40 by vdragomi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
DESCRIPTION
	The strlcpy() function copies strings respectively. It is designed
	to be safer, more consistent, and less error prone replacement strncpy(3).
	Unlike those function, strlcpy() take the full size of the buffer (not
	just the length) and guarantee to NUL-terminate the result (as long as
	size is larger than 0). Note that a byte for the NUL  should be included
	in size.  Also note thatstrlcat() only operates on true “C” strings.
	This means for strlcpy() src must be NUL-terminated. The strlcpy() function
	copies up to size - 1 characters from the NUL-terminated string src to dst,
	NUL-terminating the result.
RETURN VALUE
	The strlcat() function returns the total length of the string they tried to
	create. That means the length of src. While this may seem somewhat confusing,
	it was done to make truncation detection simple.
*/

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	i;

	if (!dst || !src)
		return (0);
	i = 0;
	if (size == 0)
		return (ft_strlen((char *)src));
	while (i < size - 1 && src[i] != '\0')
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	while (src[i] != '\0')
		i++;
	return (i);
}

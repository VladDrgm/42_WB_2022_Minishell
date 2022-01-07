/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdragomi <vdragomi@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 14:54:46 by vdragomi          #+#    #+#             */
/*   Updated: 2021/12/14 14:54:46 by vdragomi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
DESCRIPTION
	The memcmp() function compares the first n bytes (each interpreted as
	unsigned char) of the memory areas s1 and s2.
RETURN VALUE
	The memcmp() function returns an integer less than, equal to, or greater
	than zero if the first n bytes of s1 is found, respectively, to be less than,
	to match, or be greater than the first n bytes of s2.
	For a nonzero return value, the sign is determined by the sign of the
	difference between the first pair of bytes (interpreted as unsigned char)
	that differ in s1 and s2.
	If n is zero, the return value is zero.
*/

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t			i;
	unsigned char	*s1_p;
	unsigned char	*s2_p;

	i = 0;
	s1_p = (unsigned char *)s1;
	s2_p = (unsigned char *)s2;
	if (n == 0)
		return (0);
	while (i < n - 1 && s1_p[i] == s2_p[i])
		i++;
	return (s1_p[i] - s2_p[i]);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamuller <mamuller@student.42wolfsburg>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/15 20:43:47 by mamuller          #+#    #+#             */
/*   Updated: 2021/11/15 20:43:47 by mamuller         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
DESCRIPTION
	The strdup() function returns a pointer to a new string which is a
	duplicate of the string s. Memory for the new string is obtained with
	malloc(3), and can be freed with free(3).
RETURN VALUE
	On success, the strdup() function returns a pointer to the duplicated
	string. It returns NULL if insufficient memory was available, with errno
	set to indicate the cause of the error.
*/

#include "libft.h"

char	*ft_strdup(const char *s)
{
	char	*dest;

	dest = malloc(ft_strlen((char *)s) + 1);
	ft_strlcpy(dest, s, ft_strlen((char *)s) + 1);
	return (dest);
}

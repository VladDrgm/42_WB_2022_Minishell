/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamuller <mamuller@student.42wolfsburg>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/15 20:40:50 by mamuller          #+#    #+#             */
/*   Updated: 2021/11/15 20:40:50 by mamuller         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
DESCRIPTION
	Allocates (with malloc(3)) and returns a substring from the string ’s’.
	The substring begins at index ’start’ and is of maximum size ’len’.
RETURN VALUE
	The substring. NULL if the allocation fails.
*/

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*return_s;
	size_t	i;

	if (!s)
		return (NULL);
	if (start >= ft_strlen(s))
		return_s = malloc(1);
	else
		return_s = malloc(sizeof(char) * len + 1);
	i = 0;
	if (return_s == NULL)
		return (NULL);
	while (i < len && start < ft_strlen(s))
	{
		return_s[i] = s[start + i];
		i++;
	}
	return_s[i] = '\0';
	return (return_s);
}

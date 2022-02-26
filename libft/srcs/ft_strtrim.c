/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbanfi <dbanfi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/26 16:51:52 by dbanfi            #+#    #+#             */
/*   Updated: 2022/02/26 16:51:52 by dbanfi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
DESCRIPTION
	Allocates (with malloc(3)) and returns a copy of ’s1’ with the characters
	specified in ’set’ removed from the beginning and the end of the string.
RETURN VALUE
	The trimmed string. NULL if the allocation fails.
*/

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	int		start;
	int		end;
	char	*dest;

	if (!s1 || !set)
		return (NULL);
	start = 0;
	end = ft_strlen(s1);
	while (ft_strchr(set, s1[start]))
		start++;
	while (ft_strchr(set, s1[end]) && end > 0)
		end--;
	if (end - start > 0)
	{
		dest = ft_calloc((sizeof(char) * (end - start)) + 1 + 1, 1);
		if (dest == NULL)
			return (NULL);
		ft_memcpy(dest, (const void *)(s1 + start), end - start + 1);
	}
	else if (end == 0)
		dest = ft_calloc((sizeof(char) * 1), 1);
	else
		dest = NULL;
	return (dest);
}

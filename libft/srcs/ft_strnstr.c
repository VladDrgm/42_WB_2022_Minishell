/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbanfi <dbanfi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/26 16:51:39 by dbanfi            #+#    #+#             */
/*   Updated: 2022/02/26 16:51:39 by dbanfi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
DESCRIPTION
	The strnstr() function locates the first occurrence of the null-terminated
	string little in the string big, where not more than len characters are
	searched. Characters that appear after a ‘\0’ character are not searched.
	Since the strnstr() function is a FreeBSD specific API, it should only be
	used when portability is not a concern.
RETURN VALUE
	If little is an empty string, big is returned; if little occurs nowhere
	in big, NULL is returned; otherwise a pointer to the first character of
	the first occurrence of little is returned.
*/

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;

	i = 0;
	if (ft_strlen(little) == 0)
		return ((char *)big);
	while (i <= ((ft_strlen(big) - ft_strlen(little)))
		&& i < len && *little != '\0')
	{
		if (ft_strncmp(big + i, little, ft_strlen(little)) == 0
			&& i + ft_strlen(little) <= len)
		{
			return ((char *)(big + i));
		}
		i++;
	}
	return (NULL);
}

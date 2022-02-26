/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbanfi <dbanfi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/26 16:51:46 by dbanfi            #+#    #+#             */
/*   Updated: 2022/02/26 16:51:46 by dbanfi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
DESCRIPTION
	The strrchr() function returns a pointer to the last occurrence of the
	character c in the string s.
RETURN VALUE
	The strrchr() function returns a pointer to the matched
	character or NULL if the character is not found. The terminating null
	byte is considered part of the string, so that if c is specified as '\0',
	these functions return a pointer to the terminator.
*/

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int	i;
	int	last;
	int	count;

	i = 0;
	last = 0;
	count = 0;
	if ((char)c == '\0')
		return ((char *)s + ft_strlen(s));
	while (s[i] != '\0')
	{
		if (s[i] == c)
		{
			last = i;
			count++;
		}
		i++;
	}
	if (count != 0)
		return ((char *)&s[last]);
	else
		return (NULL);
}

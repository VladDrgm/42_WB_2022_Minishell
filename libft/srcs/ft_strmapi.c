/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbanfi <dbanfi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/26 16:51:24 by dbanfi            #+#    #+#             */
/*   Updated: 2022/02/26 16:51:24 by dbanfi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
DESCRIPTION
	Applies the function ’f’ to each character of the string ’s’ to create a
	new string (with malloc(3)) resulting from successive applications of ’f’.
RETURN VALUE
	The string created from the successive applications of ’f’. Returns NULL
	if the allocation fails.
*/

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	int				i;
	char			*str;

	if (!s || !f)
		return (NULL);
	i = 0;
	str = ft_strdup(s);
	if (str == NULL)
		return (NULL);
	while (str[i] != '\0')
	{
		str[i] = f(i, str[i]);
		i++;
	}
	return (str);
}

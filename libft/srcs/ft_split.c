/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdragomi <vdragomi@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 14:55:17 by vdragomi          #+#    #+#             */
/*   Updated: 2021/12/14 14:55:17 by vdragomi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
DESCRIPTION
	Allocates (with malloc(3)) and returns an array of strings obtained by
	splitting ’s’ using the character ’c’ as a delimiter. The array must be
	ended by a NULL pointer.
RETURN VALUE
	The array of new strings resulting from the split. NULL if the allocation
	fails.
*/

#include "libft.h"

static int	ft_wcount(char const *str, char c)
{
	int		word;
	char	*tmp;
	char	*tmp_free;

	if (c == '\0')
		return (1);
	else if (ft_strlen(str) == 0)
		return (0);
	word = 0;
	tmp = ft_strdup((char *)str);
	if (!tmp)
		return (0);
	tmp_free = tmp;
	while (tmp != NULL)
	{
		if (*(tmp + 1) != c || *tmp != c)
			word = word + 1;
		tmp = ft_strchr(tmp + 1, c);
	}
	if (str[ft_strlen(str) - 1] == c)
		word--;
	free(tmp_free);
	return (word);
}

char	**ft_split(char const *str, char c)
{
	char	**temp;
	int		word;
	int		start;
	int		len;

	if (!str)
		return (NULL);
	temp = ft_calloc(sizeof(char *) * (ft_wcount(str, c) + 1), 1);
	word = 0;
	start = 0;
	len = 0;
	while (str[start + len] != '\0' && temp != NULL)
	{
		start = start + len;
		len = 0;
		while (str[start] == c && str[start] != '\0')
			start++;
		while (str[start + len] != c && str[start + len] != '\0')
			len++;
		if (str[start + len - 1] != c)
			temp[word] = ft_substr(str, start, len);
		word++;
	}
	return (temp);
}

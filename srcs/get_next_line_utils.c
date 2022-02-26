/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbanfi <dbanfi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/26 16:41:02 by dbanfi            #+#    #+#             */
/*   Updated: 2022/02/26 16:41:02 by dbanfi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/minishell.h"

char	*ft_strchr_gnl(const char *s, int c)
{
	int	i;

	i = 0;
	if (!s)
		return (NULL);
	while (s[i] != '\0' && s[i] != c)
		i++;
	if (s[i] == c)
		return ((char *)&s[i]);
	else
		return (NULL);
}

size_t	ft_strlen_gnl(char *s)
{
	int	len;

	len = 0;
	if (!s || s[0] == 0)
		return (0);
	while (s[len] != '\0')
		len++;
	return (len);
}

char	*ft_strjoin_gnl(char *s1, char *s2, int j)
{
	char	*return_s;
	int		len_s1;
	int		len_s2[2];
	int		i;

	i = 0;
	if (!s1 || !s2)
		return (NULL);
	len_s1 = ft_strlen(s1);
	len_s2[0] = ft_strlen(s2);
	len_s2[1] = len_s2[0] - (ft_strchr(s2, '\0') - ft_strchr(s2, '\n'));
	return_s = malloc(sizeof(char) * (len_s1 + len_s2[j] + 1) + 1);
	if (return_s == NULL)
		return (NULL);
	while (i < len_s1 + len_s2[j] + 1)
	{
		if (i < len_s1)
			return_s[i] = s1[i];
		else
			return_s[i] = s2[i - len_s1];
		i++;
	}
	return_s[(len_s1 + len_s2[j] + 1)] = '\0';
	free(s1);
	return (return_s);
}

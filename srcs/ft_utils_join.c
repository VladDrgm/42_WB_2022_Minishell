/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils_join.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbanfi <dbanfi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/26 13:04:50 by dbanfi            #+#    #+#             */
/*   Updated: 2022/02/26 15:25:04 by dbanfi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/minishell.h"

/**
	@brief Joins strings s1 and s2, frees s1.
	@param s1: First string to join.
	@param s2: Second string to join.
	@return Returns joined string.
*/
char	*ft_strjoin_with_free(char *s1, char const *s2)
{
	char	*return_s;

	if (!s1 || !s2)
		return (NULL);
	return_s = ft_calloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2)) + 1, 1);
	if (return_s == NULL)
		return (NULL);
	ft_memcpy(return_s, s1, ft_strlen(s1));
	ft_memcpy(return_s + ft_strlen(s1), s2, ft_strlen(s2));
	if (s1 != NULL)
		free (s1);
	s1 = NULL;
	return (return_s);
}

/**
	@brief Joins strings s1 and s2, both strings.
	@param s1: First string to join.
	@param s2: Second string to join.
	@return Returns joined string.
*/
char	*ft_strjoin_with_dfree(char *s1, char *s2)
{
	char	*return_s;

	if (!s1 || !s2)
		return (NULL);
	return_s = ft_calloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2)) + 1, 1);
	if (return_s == NULL)
		return (NULL);
	ft_memcpy(return_s, s1, ft_strlen(s1));
	ft_memcpy(return_s + ft_strlen(s1), s2, ft_strlen(s2));
	if (s1 != NULL)
		free (s1);
	s1 = NULL;
	if (s2 != NULL)
		free (s2);
	s2 = NULL;
	return (return_s);
}

/**
	@brief Joins strings s1 and s2, frees s2.
	@param s1: First string to join.
	@param s2: Second string to join.
	@return Returns joined string.
*/
char	*ft_strjoin_with_scnd_free(char *s1, char *s2)
{
	char	*return_s;

	if (!s1 || !s2)
		return (NULL);
	return_s = ft_calloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2)) + 1, 1);
	if (return_s == NULL)
		return (NULL);
	ft_memcpy(return_s, s1, ft_strlen(s1));
	ft_memcpy(return_s + ft_strlen(s1), s2, ft_strlen(s2));
	if (s2 != NULL)
		free (s2);
	s2 = NULL;
	return (return_s);
}

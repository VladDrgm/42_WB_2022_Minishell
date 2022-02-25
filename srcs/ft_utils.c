/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbanfi <dbanfi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/26 13:04:50 by dbanfi            #+#    #+#             */
/*   Updated: 2022/02/26 13:04:50 by dbanfi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/minishell.h"

/**
	@brief Compares two strings.
	@param s1: First string to compare.
	@param s2: Second string to compare.
	@return Returns value different from 0 if strings different.
*/
int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] == s2[i] && s1[i] != '\0' && s2[i] != '\0')
		i++;
	return (s1[i] - s2[i]);
}

/**
	@brief Gets actual current working directory and saves it into 
		variable.
	@param env: Variable that gets a string.
	@return None.
*/
void	ft_set_global_pwd(char **env)
{
	int	i;

	i = 1;
	if (*env)
		free(*env);
	*env = getcwd(NULL, 0);
	while (getcwd(*env, i) == NULL)
		i++;
}

/**
	@brief Frees and sets pointer to NULL. Is NULL protected.
	@param s1: Pointer to a pointer to be freed.
	@return None.
*/
void	ft_smart_free(void **ptr)
{
	if (*ptr != NULL)
		free(*ptr);
	*ptr = NULL;
}

/**
	@brief Frees NULL terminated string array.
	@param s1: String array to be freed.
	@return None.
*/
void	ft_free_split(char **split)
{
	int	i;

	i = 0;
	while (split[i] != NULL)
	{
		free(split[i]);
		i++;
	}
	free(split);
}

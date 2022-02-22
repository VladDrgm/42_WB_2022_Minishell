/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env_check.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamuller <mamuller@student.42wolfsburg>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/22 12:24:09 by mamuller          #+#    #+#             */
/*   Updated: 2022/02/22 12:24:09 by mamuller         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/minishell.h"

/**
	 @brief Loops through the env list and searches for the respective value
	 		to given env name.
	 @param str Name of the env variabel to search for.
	 @return The respective env value or if not found NULL .
	 @exception For empty PWD global variables are used as return value.
 */
static char	*ft_env_lst_search(char *str, int search_len)
{
	t_env_var	*temp_env;
	t_list		*temp;

	temp = g_access.env;
	while (temp)
	{
		temp_env = (t_env_var *)(temp->content);
		if (search_len == (int)(ft_strlen(temp_env->name) - 1))
		{
			if (!(ft_strncmp(str, temp_env->name, search_len)))
			{
				if (!(ft_strncmp(temp_env->name, "PWD=", \
					ft_strlen(temp_env->name))) && g_access.dp != NULL)
				{
					if (*(temp_env->value) != '\0')
						return (g_access.dp);
				}
				else
					return (temp_env->value);
			}
		}
		temp = temp->next;
	}
	return (NULL);
}

/**
	 @brief Gets the env value depending on the given str (env key).
	 @param str Name of the env variabel to search for.
	 @return None.
	 @exception $? returns the global variable for the last exit value.
	 @exception For unset PWD global variables are used as return value.
 */
static char	*ft_getenv(char *str)
{
	int		search_len;
	char	*return_str;

	if (!str)
		return ("");
	search_len = ft_strlen(str);
	if (str[0] == '?' && search_len == 1)
		return (g_access.last_return);
	return_str = ft_env_lst_search(str, search_len);
	if (return_str != NULL)
		return (return_str);
	if (!ft_strncmp(str, "PWD", ft_strlen(str)) && g_access.pwd != NULL)
	{
		if (g_access.dp != NULL)
			return (g_access.dp);
		else
			return (g_access.pwd);
	}
	return ("");
}

/**
	 @brief Replaces the user input env var ($) wit the respective value 
	 	of the env var.
	 @param args Pointer to a string of users input.
	 @param i Index of the start point of the variable name.
	 @param j Index of the end point of the variable name.
	 @return None.
 */
static void	ft_env_replace(char **args, int i, int j)
{
	char	*temp1;
	char	*temp0;

	temp1 = ft_substr(*args, i + 1, j - i - 1);
	temp0 = ft_getenv(temp1);
	ft_smart_free((void **)&temp1);
	(*args)[i] = '\0';
	temp1 = ft_strjoin(*args, temp0);
	temp0 = ft_strjoin(temp1, &((*args)[j]));
	i = ft_strlen(temp1);
	ft_smart_free((void **)args);
	*args = temp0;
	ft_smart_free((void **)&temp1);
}

/**
	 @brief Finds env var names in string and calls fuction to replace them.
	 @param s Pointer to a string of users input.
	 @param s_quote_flag Amount of single quotes before current call.
	 @param i Pointer to index of the start point of the variable name.
	 @param j Pointer to index of the end point of the variable name.
	 @return 1 on found env var name else 0.
	 @exception Doesn't look in single quote surronded strings (as they are not 
	 	transformed).
 */
static int	ft_env_finder(char **s, int s_quote_flag, int *i, int *j)
{
	if (s_quote_flag % 2 == 0)
	{
		*j = *i + 1;
		while (ft_isalnum((*s)[*j]) || (*s)[*j] == FT_UNDERSCORE)
		{
			(*j)++;
			if (ft_isdigit((*s)[*j - 1]))
				break ;
		}
		if (*j == *i + 1)
		{
			if ((*s)[*j] == '*' || (*s)[*j] == '@' || (*s)[*j] == '#' || \
				(*s)[*j] == '?' || (*s)[*j] == '-' || (*s)[*j] == '$' || \
				(*s)[*j] == '!')
				(*j)++;
			else
			{
				(*i)++;
				return (0);
			}
		}
		ft_env_replace(s, *i, *j);
		(*i)--;
	}
	return (1);
}

/**
	 @brief Checks and replaces string on env variables input ($) if needed.
	 @param args Pointer to a string of users input.
	 @return None.
 */
void	ft_env_check(char **args)
{
	int	i;
	int	j;
	int	s_quote_flag;
	int	d_quote_flag;

	i = 0;
	j = 0;
	s_quote_flag = 0;
	d_quote_flag = 0;
	while ((*args)[i])
	{
		if ((*args)[i] == FT_SINGLE_QUOTE)
			if (d_quote_flag % 2 == 0)
				s_quote_flag++;
		if ((*args)[i] == FT_DOUBLE_QUOTE)
			if (s_quote_flag % 2 == 0)
				d_quote_flag++;
		if ((*args)[i] == FT_DOLLAR_SIGN)
			if (ft_env_finder(args, s_quote_flag, &i, &j) == 0)
				continue ;
		i++;
	}
}

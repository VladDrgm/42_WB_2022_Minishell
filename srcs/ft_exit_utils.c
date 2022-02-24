/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbanfi <dbanfi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/25 16:28:20 by dbanfi            #+#    #+#             */
/*   Updated: 2022/02/25 16:28:20 by dbanfi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/minishell.h"

/**
	@brief
	@param argv
	@return Int.
 */
int	ft_digit_check(char *argv)
{
	int	i;

	i = 0;
	while (argv[i])
	{
		if (ft_isdigit(argv[i]) == 0 && i != 0)
			return (1);
		else if ((ft_isdigit(argv[i]) == 1) || (argv[0] == '-'))
			i++;
		else
			i++;
	}
	if ((argv[0] == '-') && !(argv[1]))
		return (1);
	return (0);
}

/**
	@brief
	@param str
	@param i
	@param j
	@return None.
 */
static void	ft_atoll_sign_checker(const char *str, int *i, int *j)
{
	if (str[*i] == '-' || str[*i] == '+')
	{
		if (str[*i] == '-')
			*j = -1;
		(*i)++;
	}
}

/**
	@brief
	@param str
	@param out
	@return Int.
 */
int	ft_atoll(const char *str, long long int *out)
{
	int				i;
	int				j;
	long long int	k;
	long long int	old_k;

	i = 0;
	j = 1;
	k = 0;
	old_k = 0;
	while (str[i] != '\0' && (str[i] == ' ' || (str[i] > 8 && str[i] < 14)))
		i++;
	ft_atoll_sign_checker(str, &i, &j);
	while (str[i] != '\0' && (str[i] > 47 && str[i] < 58))
	{
		k = k * 10 + (str[i] - 48);
		if (k < old_k)
			return (1);
		old_k = k;
		i++;
	}
	*out = k * j;
	return (0);
}

/**
	@brief
	@return Int.
 */
int	ft_get_index(void)
{
	t_list	*ptr;
	int		index;

	index = 0;
	ptr = g_access.parser2exec;
	while (ptr)
	{
		index++;
		ptr = ptr->next;
	}
	return (index);
}

/**
	@brief
	@param str1
	@param str2
	@param str3
	@param exit_value
	@return None.
 */
int	ft_exit_error_handler(char *str1, char *str2, char *str3, int exit_value)
{
	if (ft_strncmp(str1, "exit\n", ft_strlen(str1)))
		write(2, str1, ft_strlen(str1));
	else
		write(1, str1, ft_strlen(str1));
	if (str2 != NULL)
		write(2, str2, ft_strlen(str2));
	if (str3 != NULL)
		write(2, str3, ft_strlen(str3));
	exit(exit_value);
}

/**
	@brief
	@param exit_value
	@return None.
 */
void	ft_child_exit(int exit_value)
{
	free_global();
	close(STDERR_FILENO);
	close(STDIN_FILENO);
	close(STDOUT_FILENO);
	exit(exit_value);
}

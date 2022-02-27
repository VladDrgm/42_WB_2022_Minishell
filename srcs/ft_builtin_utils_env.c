/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtins_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbanfi <dbanfi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/25 17:29:14 by dbanfi            #+#    #+#             */
/*   Updated: 2022/02/25 17:29:14 by dbanfi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/minishell.h"

/**
	@brief Finds the value of env var
	@param name Serached key.
	@return Value of found env var else NULL
 */
char	*env_value_finder(char *name)
{
	t_list	*ptr;

	ptr = g_access.env;
	while (ptr != NULL)
	{
		if (!ft_strncmp(((t_env_var *)(ptr->content))->name, name, \
			ft_strlen(name)))
		{
			if (((t_env_var *)(ptr->content))->value != NULL)
				return (((t_env_var *)(ptr->content))->value);
		}
		ptr = ptr->next;
	}
	return (NULL);
}

/**
	@brief Updates value of already exisisting env.
	@param to_search The string to be looked for inside the env variable
	@param to_replace The string that will replace 'to_search'
	@return None.
 */
void	ft_update_env(char *to_search, char *to_replace)
{
	t_list	*ptr;

	ptr = g_access.env;
	while (ptr != NULL)
	{
		if (!ft_strncmp(((t_env_var *)(ptr->content))->name, \
			to_search, ft_strlen(to_search)))
		{
			if (((t_env_var *)(ptr->content))->value != NULL)
				free(((t_env_var *)(ptr->content))->value);
			((t_env_var *)(ptr->content))->value = NULL;
			((t_env_var *)(ptr->content))->value = ft_strdup(to_replace);
		}
		ptr = ptr->next;
	}
}

/**
	@brief Updates already existing env var else creates new env var.
	@param env Key of env var.
	@param value New value of env var.
	@param pid Proccess id.
	@return None.
 */
void	ft_update_create_env(char *env, char *value, pid_t pid)
{
	t_list	*ptr;
	char	*args[3];

	ptr = g_access.env;
	while (ptr != NULL)
	{
		if (ft_strncmp(((t_env_var *)(ptr->content))->name, env, \
			ft_strlen(env)) == 0)
		{
			if ((ft_strlen(((t_env_var *)(ptr->content))->name) - 1) == \
				ft_strlen(env))
			{
				ft_smart_free((void **)&(((t_env_var *)(ptr->content))->value));
				((t_env_var *)(ptr->content))->value = ft_strdup(value);
				return ;
			}
		}
		ptr = ptr->next;
	}
	args[0] = "export";
	args[1] = ft_strjoin_with_free(ft_strjoin(env, "="), value);
	args[2] = NULL;
	minishell_export(args, pid);
	ft_smart_free((void **)&args[1]);
}

/**
	@brief Prints the correct error message according to calling function.
	@param mes_type Type of calling function for error message.
	@param args_word String to be checked.
	@return None.
 */
static void	ft_env_name_check_error_print(int mes_type, char *args_word)
{
	if (mes_type == FT_EXPORT_MES_TYPE)
		write(2, "minishell: export: `", 20);
	else if (mes_type == FT_UNSET_MES_TYPE)
		write(2, "minishell: unset: `", 19);
	write(2, args_word, ft_strlen(args_word));
	write(2, "': not a valid identifier\n", 26);
}

/**
	@brief Checks if args_word is valid env var key.
	@param args_word String to be checked.
	@param valid Validity check flag of args_word.
	@param pid Proccess id.
	@param mes_type Type of calling function for error message.
	@return None.
 */
int	ft_env_name_check(char *args_word, int *valid, pid_t pid, int mes_type)
{
	int	j;

	j = 0;
	*valid = 1;
	while (args_word[j] != '=' && args_word[j] != '\0')
	{
		if (j == 0 && (args_word[j] == '_' || ft_isalpha(args_word[j])))
			j++;
		else if (j > 0 && (args_word[j] == '_' || ft_isalnum(args_word[j])))
			j++;
		else
		{
			*valid = 0;
			if (pid == 0)
				ft_env_name_check_error_print(mes_type, args_word);
			ft_set_lasts(NULL, 0, 1, FT_LAST_RETURN_MODE);
			break ;
			j++;
		}
	}
	return (j);
}

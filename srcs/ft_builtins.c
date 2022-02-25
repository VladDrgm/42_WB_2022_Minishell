/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtins.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbanfi <dbanfi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/25 16:20:24 by dbanfi            #+#    #+#             */
/*   Updated: 2022/02/25 16:20:24 by dbanfi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/minishell.h"

/**
	 @brief Bultin command: env.
	 @param args List of args
	 @return Always returns 1, to continue executing.
 */
int	minishell_env(char **args, pid_t pid)
{
	t_list	*ptr;

	ft_set_lasts(args, pid, 0, FT_LAST_FULL_MODE);
	if (ft_strncmp(args[0], "env", 3))
		return (0);
	ptr = g_access.env;
	if (pid == 0)
	{
		while (ptr != NULL)
		{
			if (((t_env_var *)(ptr->content))->value != NULL)
			{
				write(1, ((t_env_var *)(ptr->content))->name, \
					ft_strlen(((t_env_var *)(ptr->content))->name));
				write(1, ((t_env_var *)(ptr->content))->value, \
					ft_strlen(((t_env_var *)(ptr->content))->value));
				write(1, "\n", 1);
			}
			if (ptr->next != NULL)
				ptr = ptr->next;
			else
				break ;
		}
	}
	return (1);
}

static void	ft_exit_multiple_child_handler(int *i, char **args)
{
	long long int	nb;

	while (args[*i] != NULL)
		(*i)++;
	if (*i > 2 && !ft_digit_check(args[1]))
		ft_child_exit(1);
	else if (*i == 1)
		ft_child_exit(ft_atoi(g_access.last_return));
	else if (!ft_digit_check(args[1]))
	{
		if (ft_atoll(args[1], &nb))
			ft_child_exit(255);
		if (!((nb < 0 && args[1][0] != '-') || (nb > 0 && args[1][0] == '-')))
		{
			if (nb >= 0 && nb <= 255)
				ft_child_exit(nb);
			else if (nb > 255)
				ft_child_exit(nb % 256);
			else if (nb < 0)
				ft_child_exit(256 - ((nb * -1) % 256));
		}
	}
	else if (*i >= 2)
		ft_child_exit(255);
	ft_child_exit(2);
}

static void	ft_exit_value_cast(char **args)
{
	long long int	num_arg;
	int				err;

	err = ft_atoll(args[1], &num_arg);
	if (err)
		ft_exit_error_handler("exit\nminishell: exit: ", \
			args[1], ": numeric argument required\n", 255);
	if (!((num_arg < 0 && args[1][0] != '-') || \
		(num_arg > 0 && args[1][0] == '-')))
	{
		if (num_arg >= 0 && num_arg <= 255)
			ft_exit_error_handler("exit\n", NULL, NULL, num_arg);
		else if (num_arg > 255)
			ft_exit_error_handler("exit\n", NULL, NULL, num_arg % 256);
		else if (num_arg < 0)
			ft_exit_error_handler("exit\n", NULL, NULL, \
				256 - ((num_arg * -1) % 256));
	}
}

static void	ft_exit_parent_handler(int *i, char **args)
{
	while (args[*i] != NULL)
		(*i)++;
	if (*i > 2 && !ft_digit_check(args[1]))
	{
		write(2, "minishell: exit: too many arguments\n", 36);
		ft_set_lasts(NULL, 0, 1, FT_LAST_RETURN_MODE);
		return ;
	}
	else if (*i == 1)
		ft_exit_error_handler("exit\n", NULL, NULL, \
		ft_atoi(g_access.last_return));
	else if (!ft_digit_check(args[1]))
		ft_exit_value_cast(args);
	else if (*i >= 2)
		ft_exit_error_handler("exit\nminishell: exit: ", \
			args[1], ": numeric argument required\n", 255);
	exit(4);
}

/**
	 @brief Builtin command: exit.
	 @param args List of args.	Not examined.
	 @return Always returns 0, to terminate execution.
	 @todo free linked lists etc properly; fix arguments that need to be passed!
 */
int	minishell_exit(char **args, pid_t pid)
{
	int	i;
	int	counter;

	i = 0;
	ft_set_lasts(args, pid, 0, FT_LAST_ARG_MODE);
	counter = ((t_command *)ft_lstlast(g_access.parser2exec)->content)->index;
	if (counter == 0 && pid != 0)
	{
		ft_exit_parent_handler(&i, args);
		return (1);
	}
	else if (counter == 0 && pid == 0)
	{
		while (args[i] != NULL)
			i++;
		if (i > 2 && !ft_digit_check(args[1]))
			ft_child_exit(1);
	}
	else if (counter != 0 && pid == 0)
		ft_exit_multiple_child_handler(&i, args);
	return (0);
}

/**
	@brief Builtin command: pwd.
	@param args List of args.	Not examined. (and no need to)
	@return Always returns 1, to continue execution.
 */
int	minishell_pwd(char **args, pid_t pid)
{
	char	*buf;
	int		i;

	i = 1;
	ft_set_lasts(args, pid, 0, FT_LAST_FULL_MODE);
	if (args[0] == NULL)
		return (0);
	if (pid == 0)
	{
		if (g_access.dp == NULL)
		{
			buf = getcwd(NULL, 0);
			while (getcwd(buf, i) == NULL)
				i++;
			write(1, buf, ft_strlen(buf));
			free(buf);
		}
		else
			write(1, g_access.dp, ft_strlen(g_access.dp));
		write(1, "\n", 1);
	}
	return (1);
}

static void	ft_env_name_check_error_print(int mes_type, char *args_word)
{
	if (mes_type == FT_EXPORT_MES_TYPE)
		write(2, "minishell: export: `", 20);
	else if (mes_type == FT_UNSET_MES_TYPE)
		write(2, "minishell: unset: `", 19);
	write(2, args_word, ft_strlen(args_word));
	write(2, "': not a valid identifier\n", 26);
}

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

static void	ft_export_add_env(char **args, int i, int j, int valid)
{
	t_env_var	*env_var;

	if ((args[i][j] == '=' || args[i][j] == '\0') && valid)
	{
		env_var = (t_env_var *)malloc(sizeof(t_env_var));
		if (args[i][j] == '=')
		{
			env_var->name = ft_substr(args[i], 0, j + 1);
			env_var->value = ft_strdup(&(args[i][j + 1]));
		}
		else
		{
			env_var->name = ft_strdup(&(args[i][0]));
			env_var->value = NULL;
		}
		if (!ft_check_existing_env(&env_var))
			ft_lstadd_back(&(g_access.env), ft_lstnew(env_var));
	}
}

/**
	@brief Builtin command: export.
	@param args List of args.	Not examined. (and no need to)
	@return Always returns 1, to continue execution.
 */
int	minishell_export(char **args, pid_t pid)
{
	int	len;
	int	j;
	int	i;
	int	valid;

	len = 0;
	while (args[len] != 0)
		len++;
	valid = 1;
	ft_set_lasts(NULL, pid, 0, FT_LAST_RETURN_MODE);
	if (args[1] == NULL && pid == 0)
	{
		ft_last_arg(args, pid);
		return (ft_single_export());
	}
	i = 1;
	while (i < len)
	{
		j = ft_env_name_check(args[i], &valid, pid, FT_EXPORT_MES_TYPE);
		ft_export_add_env(args, i, j, valid);
		i++;
	}
	ft_last_arg(args, pid);
	return (1);
}

static void	ft_unset_first_node(t_list *ptr, char **args, int i, int valid)
{
	if (ft_strlen(args[i]) == \
		ft_strlen(((t_env_var *)(ptr->content))->name) - 1 && valid)
	{
		if (!ft_strncmp(args[i], ((t_env_var *)(ptr->content))->name, \
			ft_strlen(args[i])))
		{
			if (ft_strncmp(args[i], "_", ft_strlen(args[i])))
			{
				g_access.env = ptr->next;
				ft_lstdelone(ptr, delone);
			}
		}
	}
}

static void	ft_unset_middle_node(t_list *ptr, int i, char **args)
{
	t_list	*temp;

	if (ft_strncmp(args[i], "_", 1))
	{
		temp = ptr->next;
		ptr->next = ptr->next->next;
		ft_lstdelone(temp, delone);
	}
}

static void	ft_unset_last_node(t_list *ptr, int i, char **args)
{
	if (ft_strncmp(args[i], "_", 1))
	{
		ft_lstdelone(ptr->next, delone);
		ptr->next = NULL;
	}
}

static void	ft_unset_nonfirst_node_handler(t_list *ptr, int i, \
	char **args, int valid)
{
	while (ptr->next != NULL && valid)
	{
		if (ft_strlen(args[i]) == \
			ft_strlen(((t_env_var *)(ptr->next->content))->name) - 1)
		{
			if (!ft_strncmp(args[i], \
				((t_env_var *)(ptr->next->content))->name, ft_strlen(args[i])))
			{
				if (ptr->next->next != NULL)
					ft_unset_middle_node(ptr, i, args);
				else
					ft_unset_last_node(ptr, i, args);
				break ;
			}
		}
		ptr = ptr->next;
	}
}

/**
	@brief Builtin command: unset.
	@param args List of args.	Not examined. (and no need to)
	@return Always returns 1, to continue execution.
 */
int	minishell_unset(char **args, pid_t pid)
{
	t_list	*ptr;
	int		valid;
	int		len;
	int		i;

	valid = 1;
	ft_set_lasts(args, pid, 0, FT_LAST_FULL_MODE);
	len = 0;
	while (args[len] != 0)
		len++;
	i = 1;
	while (i < len)
	{
		ptr = g_access.env;
		ft_env_name_check(args[i], &valid, pid, FT_UNSET_MES_TYPE);
		if (!ft_strncmp(args[i], "PWD", ft_strlen(args[i])))
			ft_smart_free((void **)&(g_access.pwd));
		ft_unset_first_node(ptr, args, i, valid);
		ft_unset_nonfirst_node_handler(ptr, i, args, valid);
		i++;
	}
	return (1);
}

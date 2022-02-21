/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_initiator.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzivanov <dzivanov@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 12:12:35 by dzivanov          #+#    #+#             */
/*   Updated: 2022/02/21 12:12:35 by dzivanov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/minishell.h"

t_builtin_content	*ft_init_builtin_content(char *cmd,	\
	int (*minishell_fct)(char **args, pid_t pid), int i)
{
	t_builtin_content	*content;

	content = ft_calloc(sizeof(t_builtin_content), 1);
	content->cmd = cmd;
	content->minishell_fct = minishell_fct;
	content->index = i;
	return (content);
}

void	ft_init_builtins(void)
{
	ft_lstadd_back(&(g_access.builtins), \
	ft_lstnew(ft_init_builtin_content("echo", minishell_echo, 0)));
	ft_lstadd_back(&(g_access.builtins), \
	ft_lstnew(ft_init_builtin_content("cd", minishell_cd, 1)));
	ft_lstadd_back(&(g_access.builtins), \
	ft_lstnew(ft_init_builtin_content("pwd", minishell_pwd, 2)));
	ft_lstadd_back(&(g_access.builtins), \
	ft_lstnew(ft_init_builtin_content("export", minishell_export, 3)));
	ft_lstadd_back(&(g_access.builtins), \
	ft_lstnew(ft_init_builtin_content("unset", minishell_unset, 4)));
	ft_lstadd_back(&(g_access.builtins), \
	ft_lstnew(ft_init_builtin_content("env", minishell_env, 5)));
	ft_lstadd_back(&(g_access.builtins), \
	ft_lstnew(ft_init_builtin_content("exit", minishell_exit, 6)));
}

/*
**	WHEN CREATING ENV LIST, WE MUST ALSO ADD THE _= VARIABLE \
**	EVEN WHEN WE MANIPULATE IT IN OUR BUILTINS;
**	AT THIS MOMENT, THE _= DOES NOT EXIST;
**	COMMENTED LINES INSIDE THE FUNCTION ARE FOR TESTING PURPOSES;
*/

/*
**	 @brief Creating a copy of the original env list.
**	 @param envp Original environmental variables list.
**	 @return None.
**	 @exception As per start of a shell OLPWD is not existent.
**	 @exception As per start of a shell PWD is always existent,
**	 			even if unset in parent shell
*/

void	ft_add_env(char **envp, int i, t_env_var *env_var)
{
	int	j;

	if (ft_strncmp(envp[i], "OLDPWD", 6))
	{
		j = 0;
		while (envp[i][j] != '=' && envp[i][j] != '\0')
			j++;
		if (!ft_strncmp(envp[i], "PWD", 3))
			g_access.pwd = ft_strdup(&(envp[i][j + 1]));
		if (envp[i][j] == '=')
		{
			env_var = (t_env_var *)malloc(sizeof(t_env_var));
			env_var->name = ft_substr(envp[i], 0, j + 1);
			env_var->value = ft_strdup(&(envp[i][j + 1]));
			ft_lstadd_back(&(g_access.env), ft_lstnew(env_var));
		}
	}
}

void	ft_create_envlist(char **envp)
{
	int			i;
	t_env_var	*env_var;

	i = 0;
	env_var = NULL;
	while (envp[i])
		ft_add_env(envp, i++, env_var);
	if (g_access.pwd == NULL)
		ft_set_global_pwd(&g_access.pwd);
	if (env_value_finder("PWD") == NULL)
	{
		env_var = (t_env_var *)malloc(sizeof(t_env_var));
		env_var->name = ft_substr("PWD=", 0, 4);
		env_var->value = ft_strdup(g_access.pwd);
		ft_lstadd_back(&(g_access.env), ft_lstnew(env_var));
	}
	else if (ft_strlen(env_value_finder("PWD")) == 0)
		ft_update_env("PWD", g_access.pwd);
	if (ft_check_symlink(env_value_finder("PWD"), NULL, 0) \
	|| ft_check_symlink((g_access.pwd), NULL, 0))
		g_access.dp = ft_strdup(env_value_finder("PWD"));
	if (g_access.home == NULL)
		ft_get_home();
}

void	ft_initiator(char **envp, char *executable)
{
	g_access.signals = 0;
	g_access.inter = 0;
	g_access.last_return = ft_itoa(0);
	g_access.pwd = NULL;
	g_access.dp = NULL;
	ft_create_envlist(envp);
	ft_update_shell_env(executable);
	ft_get_PATH();
	ft_init_builtins();
	g_access.lexor2parser = NULL;
	g_access.parser2exec = NULL;
	g_access.read_line2lexor = NULL;
}

/*
**	g_access.read_line2lexor = NULL; //allocated in main by readline
*/

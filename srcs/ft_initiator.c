
#include "../incl/minishell.h"


t_builtin_content *ft_init_builtin_content(char *cmd, int (*minishell_fct)(char **args, ...), int i)
{
	t_builtin_content	*content;

	content = calloc(sizeof(t_builtin_content), 1);
	content->cmd = cmd;
	content->minishell_fct = minishell_fct;
	content->index = i;
	return(content);
}

void ft_init_builtins(void)
{
	ft_lstadd_back(&(g_access.builtins), ft_lstnew(ft_init_builtin_content("echo", minishell_echo, 0)));
	ft_lstadd_back(&(g_access.builtins), ft_lstnew(ft_init_builtin_content("cd", minishell_cd, 1)));
	ft_lstadd_back(&(g_access.builtins), ft_lstnew(ft_init_builtin_content("pwd", minishell_pwd, 2)));
	ft_lstadd_back(&(g_access.builtins), ft_lstnew(ft_init_builtin_content("export", minishell_export, 3)));
	ft_lstadd_back(&(g_access.builtins), ft_lstnew(ft_init_builtin_content("unset", minishell_unset, 4)));
	ft_lstadd_back(&(g_access.builtins), ft_lstnew(ft_init_builtin_content("env", minishell_env, 5)));
	ft_lstadd_back(&(g_access.builtins), ft_lstnew(ft_init_builtin_content("exit", minishell_exit, 6)));
}

/*
	WHEN CREATING ENV LIST, WE MUST ALSO ADD THE _= VARIABLE \
	EVEN WHEN WE MANIPULATE IT IN OUR BUILTINS;
	AT THIS MOMENT, THE _= DOES NOT EXIST;
	COMMENTED LINES INSIDE THE FUNCTION ARE FOR TESTING PURPOSES;
*/

/**
	 @brief Creating a copy of the original env list. 
	 @param envp Original environmental variables list.
	 @return None.
	 @exception As per start of a shell OLPWD is not existent.
	 @exception As per start of a shell PWD is always existent, 
	 			even if unset in parent shell
 */
void ft_create_envlist(char **envp)
{
	int i, j;
	t_env_var *env_var;

	i = 0;
	while (envp[i])
	{
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
		i++;
	}
	if (g_access.pwd == NULL)
		ft_set_global_pwd(&g_access.pwd);
	if (g_access.home == NULL)
		ft_get_home();
}

void ft_initiator(char **envp)
{
	g_access.signals = 0;
	g_access.last_return = malloc(sizeof(char) * 2);
	g_access.last_return[0] = '0';
	g_access.last_return[1] = '\0';
	g_access.pwd = NULL;
	ft_create_envlist(envp);
	ft_init_builtins();
	g_access.lexor2parser = NULL;
	g_access.parser2exec = NULL;
	g_access.read_line2lexor = NULL; //allocated in main by readline
}

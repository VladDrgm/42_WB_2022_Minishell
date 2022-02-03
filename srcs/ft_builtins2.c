#include "../incl/minishell.h"

/**
	 @brief Bultin command: change directory.
	 @param args List of args. args[0] is "cd". args[1] is the directory.
	 @return Always returns 1, to continue executing.
	 @todo CHECK IF PWD EXISTS AND CREATE IT IF IT DOESN'T, AFTER USING CD; (idea: change PWD to PWD1 if using 'unset' on PWD)
 */
int	minishell_cd(char **args, pid_t pid)
{
	char *temp[3];
	char *path;
	pid++;
	pid--;

	ft_update_env("_=", "cd");
	free(g_access.last_return);
	g_access.last_return = ft_itoa(0);

	temp[0] = ft_strdup(args[0]);
	temp[1] = ft_strjoin("OLDPWD=", g_access.pwd);
	temp[2] = NULL;
	t_list *ptr = g_access.env;
	//IMPLEMENT ACCESS IN ORDER TO TACKLE INCORRECT PATH
	path = ft_strdup(ft_handle_cd(args[1], ptr, pid));
	if (path == NULL)
	{
		if (pid == 0)
			write(2, "minishell: cd: HOME not set\n", 28);
		free(g_access.last_return);
		g_access.last_return = ft_itoa(1);
		return (1);
	}
	else if (!ft_strncmp(path, ";", 1))
	{
		if (pid == 0)
			write(2, "minishell: cd: OLDPWD not set\n", 30);
		free(g_access.last_return);
		g_access.last_return = ft_itoa(1);
		return (1);
	}
	else if (!ft_strncmp(path, "L", 1))
	{
		if (pid == 0)
			write(2, "minishell: cd: --: invalid option\n", 34);
		free(g_access.last_return);
		g_access.last_return = ft_itoa(1);
		return (1);
	}

	if ((pid == 0) && (access(path, X_OK) == -1))
	{
		perror(ft_strjoin("minishell: cd: ", path));
	}

	if (pid != 0)
	{
		ft_update_create_OLDPWD(temp, ptr, pid);
		if (chdir(path) != 0)
		{
			free(g_access.last_return);
			g_access.last_return = ft_itoa(1);
		}
		ft_update_PWD(path);
	}
	free(temp[1]);
	free(temp[0]);
	return (1);
}



/**
	 @brief Builtin command: echo.
	 @param args List of args.	Not examined.
	 @return Always returns 1, to continue execution.
	 @todo edge case fetch -nnnnn -nnnn test / edge case echo $_ -> $_ must be implemented alongside history; implemented -nnnnnnnn and also implemented -nnnnn -nnnn V.
 */
int	minishell_echo(char **args, pid_t pid)
{
	int i;
	int flag;
	int temp;
	int len;

	free(g_access.last_return);
	g_access.last_return = ft_itoa(0);
	ft_update_env("_=", "echo");
	if (pid == 0)
	{
		len = 0;
		while (args[len] != NULL)
		{
			len++;
		}
		flag = 0;
		if (args[1] == NULL)
			write(2, "minishell: expected argument to \"echo\"\n", 40);
		else
		{
			i = 1;
			while (args[i]) //go through all arguments
			{
				temp = echo_flag(args[i]); //checks for -n / -nnnnnnn and returns 1 if so or 0 if the format is not -n / -nnnnn
				flag += temp; //flag keeps growing by temp
				if (flag == 0 || temp == 0)
					break;
				else
					i++;
			}
			echo_print(args, i, len, flag); //based on the flag, we either print with or without a \n
		}
	}
	return (1);
}

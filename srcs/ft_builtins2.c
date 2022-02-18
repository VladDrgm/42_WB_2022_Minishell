#include "../incl/minishell.h"

/**
	 @brief Bultin command: change directory.
	 @param args List of args. args[0] is "cd". args[1] is the directory.
	 @return Always returns 1, to continue executing.
 */
/* int	minishell_cd(char **args, pid_t pid)
{
	char	*temp[3];
	char	*path;
	DIR		*dir;

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
		return(ft_cd_error_handler("minishell: cd: HOME not set\n", pid, &path, temp));
	else if (!ft_strncmp(path, ";", 1))
		return(ft_cd_error_handler("minishell: cd: OLDPWD not set\n", pid, &path, temp));
	else if (!ft_strncmp(path, "L", 1))
		return(ft_cd_error_handler("minishell: cd: --: invalid option\n", pid, &path, temp));
	dir = opendir(path);
	if ((pid == 0) && (dir == NULL))
	{
		free(g_access.last_return);
		g_access.last_return = ft_itoa(1);
		perror(ft_strjoin("minishell: cd: ", path));
	}
	else
		closedir(dir);
	if (pid != 0)
	{
		ft_update_create_OLDPWD(temp, ptr, pid);
		ft_update_dir(args[1], path);
		ft_update_PWD();
	}
	if (path)
		free(path);
	free(temp[1]);
	free(temp[0]);
	return (1);
} */

int minishell_cd(char **args, pid_t pid)
{
	char *abs_path;
	int sym_check;
	char *current_path;
	DIR		*dir;

	free(g_access.last_return);
	g_access.last_return = ft_itoa(0);
	if (args[1] == NULL)
	{
		if (pid == 0)
			write(2, "cd without an argument not permitted in this minishell.\n", 56);
		free(g_access.last_return);
		g_access.last_return = ft_itoa(1);
		return(1);
	}
	abs_path = NULL;
	current_path = NULL;
	ft_rtoa_path(args[1], &abs_path);
	dir = opendir(abs_path);
	if (dir == NULL)
	{
		free(g_access.last_return);
		g_access.last_return = ft_itoa(1);
		if (pid == 0)
			perror(ft_strjoin("minishell: cd: ", args[1]));
		free(g_access.last_return);
		g_access.last_return = ft_itoa(1);
		return (1);
	}
	else
		closedir(dir);
	if (g_access.dp != NULL)
		current_path = ft_strdup(g_access.dp);
	else
		ft_set_global_pwd(&current_path);
	sym_check = ft_check_symlink(abs_path, args[1], pid);
	if (sym_check == -1)
	{
		printf("TEST\n");
		free(g_access.last_return);
		g_access.last_return = ft_itoa(1);
		if (current_path != NULL)
			free(current_path);
		if (abs_path != NULL)
			free(abs_path);
		return (1);
	}
	else if (sym_check == SYMLINK)
	{
		if (env_value_finder("PWD") == NULL || ft_strlen(env_value_finder("PWD")) == 0)
			ft_update_create_OLDPWD("", pid);
		else
			ft_update_create_OLDPWD(current_path, pid);
		chdir(abs_path);
		if (g_access.dp != NULL)
			free(g_access.dp);
		g_access.dp = ft_strdup(abs_path);
		if (g_access.pwd != NULL)
			free(g_access.pwd);
		g_access.pwd = ft_strdup(abs_path);
		ft_update_env("PWD", abs_path);

	}
	else if (sym_check == NOT_SYMLINK)
	{
		if (env_value_finder("PWD") == NULL || ft_strlen(env_value_finder("PWD")) == 0)
			ft_update_create_OLDPWD("", pid);
		else
			ft_update_create_OLDPWD(current_path, pid);
		chdir(abs_path);
		if (g_access.dp != NULL)
		{
			free(g_access.dp);
			g_access.dp = NULL;
		}
		if (g_access.pwd != NULL)
			free(g_access.pwd);
		g_access.pwd = ft_strdup(abs_path);
		ft_update_env("PWD", abs_path);
	}
	if (abs_path != NULL)
		free(abs_path);
	if (current_path != NULL)
		free(current_path);
	return(1);
}





/**
	 @brief Builtin command: echo.
	 @param args List of args.	Not examined.
	 @return Always returns 1, to continue execution.
	 @todo edge case fetch -nnnnn -nnnn test / edge case echo $_ -> $_ must be implemented alongside history; implemented -nnnnnnnn and also implemented -nnnnn -nnnn V.
	 @todo fix flag -n try printing
*/
int	minishell_echo(char **args, pid_t pid)
{
	int i;
	int flag;
	int temp;
	int len;
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
			write(1, "\n", 1);
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

	free(g_access.last_return);
	g_access.last_return = ft_itoa(0);
	return (1);
}

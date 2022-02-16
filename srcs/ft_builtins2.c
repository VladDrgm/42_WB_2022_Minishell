#include "../incl/minishell.h"

/**
	 @brief Bultin command: change directory.
	 @param args List of args. args[0] is "cd". args[1] is the directory.
	 @return Always returns 1, to continue executing.
 */
int	minishell_cd(char **args, pid_t pid)
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
}

/* int minishell_cd(char **args, pid_t pid)
{
	char *path_helper;
	char *absolute_path;

	char *current_pwd;
	char *exec_pwd;
	t_list *ptr;

	ptr = g_access.env;
	current_pwd = NULL;
	exec_pwd = NULL;

	if (g_access.dp != NULL)
		path_helper = ft_strdup(g_access.dp);
	else
		path_helper = ft_strdup(g_access.pwd);
	if (ft_check_symlink(args[1]))
	{
		ft_set_global_pwd(&current_pwd);
		exec_pwd = ft_calloc(ft_strlen(executable)-ft_strlen("/minishell") + 1, sizeof(char));
		ft_strlcpy(exec_pwd,executable, ft_strlen(executable) - ft_strlen("/minishell") + 1);
		chdir(exec_pwd);
		free(exec_pwd);
		exec_pwd = NULL;
		ft_set_global_pwd(&exec_pwd);
		chdir(current_pwd);
		if (((t_env_var*)(ptr->content))->value != NULL)
			free(((t_env_var*)(ptr->content))->value);
		((t_env_var*)(ptr->content))->value = ft_strjoin(exec_pwd, "/minishell");
		if (current_pwd != NULL)
			free(current_pwd);
		current_pwd = NULL;
		if (exec_pwd != NULL)
			free(exec_pwd);
		exec_pwd = NULL;
	}
	else
	{
		chdir(args[1]);
	}

	
} */





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

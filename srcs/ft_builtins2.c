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

void	ft_cd_symlink_handler(char *abs_path, char *current_path, int pid)
{
	if (env_value_finder("PWD") == NULL || ft_strlen(env_value_finder("PWD")) == 0)
		ft_update_create_env("OLDPWD", "", pid);
	else
		ft_update_create_env("OLDPWD", current_path, pid);
	chdir(abs_path);
	ft_smart_free((void **)&g_access.dp);
	g_access.dp = ft_strdup(abs_path);
	ft_smart_free((void **)&g_access.pwd);
	g_access.pwd = ft_strdup(abs_path);
	ft_update_env("PWD", abs_path);
}

void	ft_cd_not_symlink_handler(char *abs_path, char *current_path, int pid)
{
	if (env_value_finder("PWD") == NULL || ft_strlen(env_value_finder("PWD")) == 0)
		ft_update_create_env("OLDPWD", "", pid);
	else
		ft_update_create_env("OLDPWD", current_path, pid);
	chdir(abs_path);
	ft_smart_free((void **)&g_access.dp);
	ft_smart_free((void **)&g_access.pwd);
	g_access.pwd = ft_strdup(abs_path);
	ft_update_env("PWD", abs_path);
}

static int ft_cd_open_dir_checker(char *abs_path, int pid, char **args)
{
	DIR		*dir;

	dir = opendir(abs_path);
	if (dir == NULL)
	{
		if (pid == 0)
		{
			write(2, "minishell: cd: ", 15);
			write(2, args[1], ft_strlen(args[1]));
			perror(" ");
		}
		ft_smart_free((void **)&abs_path);
		ft_set_lasts(args, pid, 1, FT_LAST_FULL_MODE);
		return (1);
	}
	else
		closedir(dir);
	return (0);
}

static void ft_cd_link_handler(char *abs_path, char *current_path, int pid, char **args)
{
	int sym_check;

	sym_check = ft_check_symlink(abs_path, args[1], pid);
	if (sym_check == -1)
	{
		ft_smart_free((void **)&current_path);
		ft_smart_free((void **)&abs_path);
		ft_set_lasts(args, pid, 1, FT_LAST_FULL_MODE);
	}
	else if (sym_check == SYMLINK)
		ft_cd_symlink_handler(abs_path, current_path, pid);
	else if (sym_check == NOT_SYMLINK)
		ft_cd_not_symlink_handler(abs_path, current_path, pid);
	ft_smart_free((void **)&abs_path);
	ft_smart_free((void **)&current_path);
}

int minishell_cd(char **args, pid_t pid)
{
	char *abs_path;
	char *current_path;

	ft_set_lasts(args, 0, 0, FT_LAST_RETURN_MODE);
	if (args[1] == NULL)
	{
		if (pid == 0)
			write(2, "cd without an argument not permitted in this minishell.\n", 56);
		ft_set_lasts(args, pid, 1, FT_LAST_FULL_MODE);
		return(1);
	}
	abs_path = NULL;
	current_path = NULL;
	ft_rtoa_path(args[1], &abs_path);
	if (ft_cd_open_dir_checker(abs_path, pid, args))
		return (1);
	if (g_access.dp != NULL)
		current_path = ft_strdup(g_access.dp);
	else
		ft_set_global_pwd(&current_path);
	ft_cd_link_handler(abs_path, current_path, pid, args);
	ft_set_lasts(args, 0, 0, FT_LAST_ARG_MODE);
	return(1);
}


static void	echo_print_handler(char **args, int len)
{
	int	flag;
	int	i;
	int	temp;

	flag = 0;
	i = 1;
	while (args[i])
	{
		temp = echo_flag(args[i]);
		flag += temp;
		if (flag == 0 || temp == 0)
			break;
		else
			i++;
	}
	echo_print(args, i, len, flag);
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
	int len;

	if (pid == 0)
	{
		len = 0;
		while (args[len] != NULL)
			len++;
		if (args[1] == NULL)
			write(1, "\n", 1);
		else
			echo_print_handler(args, len);
	}
	ft_set_lasts(args, pid, 0, FT_LAST_FULL_MODE);
	return (1);
}

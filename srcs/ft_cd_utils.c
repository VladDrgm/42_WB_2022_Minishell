#include "../incl/minishell.h"

//when UNSETTING PWD, this needs to have a special situation
void	ft_update_create_OLDPWD(char **argv, t_list *ptr, pid_t pid)
{
	while (ptr != NULL)
	{
		if (ft_strncmp(((t_env_var *)(ptr->content))->name, "OLDPWD", 6) == 0) //IF OLDPWD EXISTS, WE UPDATE IT <------
		{
			ft_set_global_pwd(&(((t_env_var *)(ptr->content))->value));
			return ;
		}
		ptr = ptr->next;
	}
	minishell_export(argv, pid); //if OLDPWD does not exist, we create it <-------------
	return ;
}

/**
	 @brief Bultin command support function: updates PWD
	 @param path The path towards the directory, as imputted by user
	 @return void functions;
	 @todo add "//" situation, where the chdir takes us to "/", but pwd should be updated as "//". Any other number of slashes must
	 		result in a single "/"
	 @todo modify PATH as imputted by user; example: we have Minishell; user imputs "minishell"; chdir works and path is 
	 		'....user/minishell' instead of '......user/Minishell'
	 @todo if we use cd "/etc" (or any variant of any below-mounting-point value), 
	 	instead of updating PWD to private/etc, we must update it to /etc (or any below mounting-point folder used)
 */
void	ft_update_PWD(void)
{
	char *path;

	path = NULL;
	ft_set_global_pwd(&path);
	if (env_value_finder("PWD") == NULL)
		ft_set_global_pwd(&g_access.pwd);
	else
		ft_update_env("PWD=", path);
	if (path != NULL)
		free(path);
}

char	*ft_handle_cd(char *address, t_list *ptr, pid_t pid)
{
	if (address == NULL)
		return (env_value_finder("HOME"));
	else if ((!ft_strncmp(address, "~", 1) && ft_strlen(address) < 2)|| (!ft_strncmp(address, "--", 2) && ft_strlen(address) < 3))
	{
		if (env_value_finder("HOME") == NULL && (!ft_strncmp(address, "~", 1) && ft_strlen(address) < 2))
			return(g_access.home);
		else
			return (env_value_finder("HOME"));
	}
	else if (!ft_strncmp(address, "-", 1) && ft_strlen(address) < 2)
	{
		while (ptr != NULL)
		{
			if (ft_strncmp(((t_env_var *)(ptr->content))->name, "OLDPWD", 6) == 0) //IF OLDPWD EXISTS, WE RETURN env_value_finder("OLDPWD") <------
			{
				if (pid == 0)
				{
					write(1, env_value_finder("OLDPWD"), ft_strlen(env_value_finder("OLDPWD")));
					write(1, "\n", 1);
				}
				return (env_value_finder("OLDPWD"));
			}
			ptr = ptr->next;
		}
		return (";");
	}
	if (!ft_strncmp(address, "---", 3))
	{
		return ("L");
	}
	else if (!ft_strncmp(address, "---", 3) && ft_strlen(address) > 3)
	{
		return ("L");
	}
	return (address);
}

int ft_cd_error_handler(char *str, pid_t pid, char **path, char **temp)
{
	if (pid == 0)
		write(2, str, ft_strlen(str));
	if (*path != NULL)
	{
		free(*path);
		*path = NULL;
	}
	free(temp[0]);
	free(temp[1]);
	free(g_access.last_return);
	g_access.last_return = ft_itoa(1);
	return (1);
}

void ft_update_dir(char *arg1, char *path)
{
	struct stat *buf;
	char *symlink;
	char *symlink_dir;

	if (arg1 == NULL)
		return;
	if (!ft_strncmp(arg1, "-", ft_strlen(arg1)))
		arg1 = env_value_finder("PWD");	//needs to be adjusted for symlink!
	buf = ft_calloc(sizeof(struct stat), 1);
	symlink = ft_strrchr(arg1, '/');
	if (lstat(arg1, buf) == -1)
		perror("minishell");
	if (S_ISLNK(buf->st_mode))
	{
		if (symlink == NULL)
		{
			ft_set_global_pwd(&g_access.dp);
			g_access.dp = ft_strjoin(g_access.dp,ft_strjoin("/", arg1));
		}
		else
		{
			symlink_dir = ft_substr(arg1, 0, symlink - arg1);
			chdir(symlink_dir);
			ft_set_global_pwd(&symlink_dir);
			free(g_access.dp);
			g_access.dp = ft_strjoin(symlink_dir, symlink);
		}
	}
	else
	{
		if(g_access.dp != NULL)
			free(g_access.dp);
		g_access.dp = NULL;
	}
	if (chdir(path) != 0)
	{
		free(g_access.last_return);
		g_access.last_return = ft_itoa(1);
	}
	free(buf);
}
